#ifndef MODULAR1CONTROLLER_H
#define MODULAR1CONTROLLER_H

#include <string>
#include <vector>
#include <memory>

class QMainWindow;
class CCommandStackController;
class CModuleManager;
class CJackConnectionManager;

class CModular1Controller
{
public:
    CModular1Controller(QMainWindow *Parent);

    bool Create(const std::string& Type, const std::string& Name);
    bool Remove(const std::string& Name);
    bool RemoveAll();
    bool Default(); //!< all existing modules to default parameters
    std::vector<std::string> GetNames() const;
    std::vector<std::string> GetSupportedTypes() const;

    void Capture();//!< capture current module/connections/parameters state
    void Restore(); //!< restore grabbed state
    void Save(const std::string& Path);
    void Load(const std::string& Path);

private:
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
    std::string m_CapturedConnections;
    std::string m_CapturedParameters;
};

#endif // MODULAR1CONTROLLER_H
