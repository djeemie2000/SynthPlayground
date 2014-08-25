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
        Created = true;
    }
    // else: not a unique name
    return Created;
}

bool CModuleManager::Remove(const std::string &Name)
{
    bool Removed = false;
    auto itModule = m_Modules.find(Name);
    if(itModule != m_Modules.end())
    {
        m_Modules.erase(itModule);
        Removed = true;
    }
    return Removed;
}

std::vector<std::string> CModuleManager::GetNames() const
{
    std::vector<std::string> AllNames;
    for(auto& Module : m_Modules)
    {
        AllNames.push_back(Module.first);
    }
    return AllNames;
}

std::vector<std::string> CModuleManager::GetSupportedTypes() const
{
    return m_Factory->GetSupportedTypes();
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
