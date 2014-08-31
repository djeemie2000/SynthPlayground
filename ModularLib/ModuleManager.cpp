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

std::vector<std::string> CModuleManager::GetNames() const
{
    std::vector<std::string> AllNames;
    for(auto& State : m_CurrentState)
    {
        AllNames.push_back(State.first);
    }
    return AllNames;
}

std::vector<std::string> CModuleManager::GetSupportedTypes() const
{
    return m_Factory->GetSupportedTypes();
}

void CModuleManager::Capture()
{
    m_GrabbedState = m_CurrentState;
}

void CModuleManager::Restore()
{
    ModuleMap RestoredModules;
    for(auto& GrabbedModule : m_GrabbedState)
    {
        auto itModule = m_Modules.find(GrabbedModule.first);
        if(itModule==m_Modules.end())
        {
            // does not exist => create into restored
            RestoredModules[GrabbedModule.first] = m_Factory->Create(GrabbedModule.second, GrabbedModule.first);

        }
        else
        {
            // else => keep
            RestoredModules[GrabbedModule.first] = itModule->second;
        }
    }

    // restore : grabbed -> current
    m_Modules = RestoredModules; // this will automatically delete all in current tha are not in restored
    m_CurrentState = m_GrabbedState;
}

void CModuleManager::Save(const std::string &Path)
{

}

void CModuleManager::Load(const std::string &Path)
{

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
