#include <sstream>
#include "ModuleManager.h"
#include "ModularModuleI.h"
#include "ModuleFactoryI.h"

CModuleManager::CModuleManager(std::shared_ptr<IModuleFactory> Factory)
    : m_Factory(Factory)
    , m_Modules()
{
}

bool CModuleManager::Create(const std::string &Type, const std::string &Name)
{
    // name should be unique!
    // if name is empty, generate 'default' name TODO
    // always check for a unique name => fail or generate?
    bool Created = false;
    std::string UsedName = Name.empty() ? GenerateUniqueName(Type) : Name;
    if(std::shared_ptr<IModularModule> Module = m_Factory->Create(Type, UsedName))
    {
        m_Modules[UsedName] = Module;
        m_CurrentState[UsedName] = Type;
        Created = true;
    }
    return Created;
}

bool CModuleManager::Remove(const std::string &Name)
{
    bool Removed = false;
    auto itModule = m_Modules.find(Name);
    auto itState = m_CurrentState.find(Name);
    if(itModule != m_Modules.end() && itState!=m_CurrentState.end())
    {
        m_Modules.erase(itModule);
        m_CurrentState.erase(itState);
        Removed = true;
    }
    return Removed;
}

bool CModuleManager::RemoveAll()
{
    Restore(ModuleState());
    return true;
}

std::vector<std::string> CModuleManager::GetNames() const
{
    std::vector<std::string> AllNames;
    for(auto& State : m_CurrentState)
    {
        AllNames.push_back(State.first);
    }
    return AllNames;
}

std::vector<std::string> CModuleManager::GetSupportedTypes(const std::string& Category) const
{
    return m_Factory->GetSupportedTypes(Category);
}

std::vector<std::string> CModuleManager::GetSupportedCategories() const
{
    return m_Factory->GetSupportedCategories();
}

void CModuleManager::Capture()
{
    m_GrabbedState = m_CurrentState;
}

void CModuleManager::Restore()
{
    Restore(m_GrabbedState);
}

void CModuleManager::Restore(const ModuleState &RestoredState)
{
    ModuleMap RestoredModules;
    for(auto& Item : RestoredState)
    {
        auto itModule = m_Modules.find(Item.first);
        if(itModule==m_Modules.end())
        {
            // does not exist => create into restored
            RestoredModules[Item.first] = m_Factory->Create(Item.second, Item.first);

        }
        else
        {
            // else => keep
            RestoredModules[Item.first] = itModule->second;
        }
    }

    // restore : grabbed -> current
    m_Modules = RestoredModules; // this will automatically delete all in current tha are not in restored
    m_CurrentState = RestoredState;
}

void CModuleManager::Export(std::string &Content)
{
    for(auto& Item : m_CurrentState)
    {
        Content += Item.first;
        Content += " --- ";
        Content += Item.second;
        Content += "\n";
    }
}

void CModuleManager::Import(const std::string &Content)
{
    ModuleState LoadedState;
    // Content string to state
    std::istringstream Iss(Content.c_str());
    do
    {
        std::string Line;
        std::getline(Iss, Line);
        if(4<=Line.length())
        {
            std::string Name = Line.substr(0, Line.find(" --- ", 0));
            std::string Type = Line.substr(Line.find(" --- ", 0)+5, std::string::npos);
            LoadedState[Name] = Type;
        }
    }
    while(!Iss.eof());

    // now restore loaded state
    Restore(LoadedState);
}

std::weak_ptr<IModularModule> CModuleManager::GetModule(const std::string &Name) const
{
    auto itModule = m_Modules.find(Name);
    return itModule != m_Modules.end() ? itModule->second : std::weak_ptr<IModularModule>();
}

const CModuleManager::ModuleState &CModuleManager::GetModuleState() const
{
    return m_CurrentState;
}

void CModuleManager::ApplyModuleState(const CModuleManager::ModuleState &ModuleState)
{
    Restore(ModuleState);
}

std::string CModuleManager::GenerateUniqueName(const std::string &Type)
{
    // try Type0, Type1, Type2, ... until it is does not exist in the current list
    int Number = 0;
    std::string Name = Type + std::to_string(Number);
    while(m_Modules.find(Name)!=m_Modules.end())
    {
        ++Number;
        Name = Type + std::to_string(Number);
    }
    return Name;
}
