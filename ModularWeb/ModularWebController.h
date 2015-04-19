#pragma once

#include <string>
#include <vector>
#include <memory>

class CCommandStackController;
class CModuleManager;
class CJackConnectionManager;
class CWebPageManager;
class CPatchManager;
struct SWebRequest;

class CModularWebController
{
public:
    CModularWebController(const std::string& PatchDirectory);
    ~CModularWebController();

    std::string HandleWebRequest(const SWebRequest& Request);

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

    bool LoadPatch(const std::string& PatchName);

    std::shared_ptr<CPatchManager> m_PatchManager;
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;

    std::shared_ptr<CWebPageManager> m_WebPageManager;
};
