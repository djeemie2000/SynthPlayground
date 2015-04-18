#pragma once

#include <string>
#include <vector>
#include <memory>

class CCommandStackController;
class CModuleManager;
class CJackConnectionManager;
class CWebPageManager;

class CModularWebController
{
public:
    CModularWebController();
    ~CModularWebController();

    std::string HandleWebRequest(const std::string& Uri);

    bool Save(const std::string& Path);
    bool Load(const std::string& Path);

private:
    bool Create(const std::string& Type, const std::string& Name);
    bool Remove(const std::string& Name);

    bool RemoveAll();
    bool Default(); //!< all existing modules to default parameters

    void Capture();//!< capture current module/connections/parameters state
    void Restore(); //!< restore grabbed state

    void UpdateModuleWebPages();

    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;

    std::shared_ptr<CWebPageManager> m_WebPageManager;
};
