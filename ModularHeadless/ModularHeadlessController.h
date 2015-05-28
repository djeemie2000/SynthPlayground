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
    ~CModularHeadlessController();

    bool RemoveAll();
    bool Default(); //!< all existing modules to default parameters

    bool Save(const std::string& Path);
    bool Load(const std::string& Path);

private:
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;
};
