#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class IModularModule;
class IModuleFactory;

class CModuleManager
{
public:
    CModuleManager(std::shared_ptr<IModuleFactory> Factory);

    bool Create(const std::string& Type, const std::string& Name);
    bool Remove(const std::string& Name);
    std::vector<std::string> GetNames() const;
    std::vector<std::string> GetSupportedTypes() const;
    void Capture();//!< capture current module state
    void Restore(); //!< restore grabbed state
    void Save(const std::string& Path); //!< save current state
    void Load(const std::string& Path); //!< load state

private:
    std::string GenerateUniqueName(const std::string& Type);

    std::shared_ptr<IModuleFactory> m_Factory;
    typedef std::map<std::string, std::shared_ptr<IModularModule>> ModuleMap;
    ModuleMap m_Modules;

    typedef std::map<std::string, std::string> ModuleState; //! module state (Name, Type)
    ModuleState m_CurrentState;
    ModuleState m_GrabbedState;
};

#endif // MODULEMANAGER_H
