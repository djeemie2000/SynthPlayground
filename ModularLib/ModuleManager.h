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
    std::vector<std::string> GetAll() const;

private:
    std::string GenerateUniqueName(const std::string& Type);

    std::shared_ptr<IModuleFactory> m_Factory;
    std::map<std::string, std::shared_ptr<IModularModule>> m_Modules;
};

#endif // MODULEMANAGER_H
