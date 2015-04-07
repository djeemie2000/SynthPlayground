#pragma once

#include <string>
#include <vector>
#include <memory>

class CCommandStackController;
class CModuleManager;
class CJackConnectionManager;

class CModularHeadlessController
{
public:
    CModularHeadlessController();

    //bool Create(const std::string& Type, const std::string& Name);
    //bool Remove(const std::string& Name);
    bool RemoveAll();
    bool Default(); //!< all existing modules to default parameters
    //std::vector<std::string> GetNames() const;
    //std::vector<std::string> GetSupportedTypes(const std::string& Category) const;
    //std::vector<std::string> GetSupportedCategories() const;

    //void Capture();//!< capture current module/connections/parameters state
    //void Restore(); //!< restore grabbed state
    bool Save(const std::string& Path);
    bool Load(const std::string& Path);

private:
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;
};
