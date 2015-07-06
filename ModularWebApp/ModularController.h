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

class CModularController
{
public:
    CModularController(const std::string& PatchDirectory);
    ~CModularController();

    bool LoadPatch(const std::string& PatchName);
    bool SavePatch(const std::string& PatchName);

    bool Create(const std::string& Type, const std::string& Name);
    bool Remove(const std::string& Name);

    bool RemoveAll();
    bool Default(); //!< all existing modules to default parameters

    void Capture();//!< capture current module/connections/parameters state
    void Restore(); //!< restore grabbed state

    const CModuleManager &GetModuleManager() const;
    const CPatchManager &GetPatchManager() const;
    CCommandStackController &GetCommandStackController();//cannot be const (yet)

private:
    bool Save(const std::string& Path);
    bool Load(const std::string& Path);

    std::shared_ptr<CPatchManager> m_PatchManager;
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;
};
