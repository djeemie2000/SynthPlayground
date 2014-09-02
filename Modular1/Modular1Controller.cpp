#include "Modular1Controller.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "ModuleGuiFactory.h"
#include "JackConnectionManager.h"

CModular1Controller::CModular1Controller(QMainWindow *Parent)
 : m_CommandStackController()
 , m_ModuleManager()
 , m_ConnectionManager()
 , m_CapturedConnections()
 , m_CapturedParameters()
{
    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    std::shared_ptr<CModuleGuiFactory> GuiFactory(new CModuleGuiFactory(Factory, m_CommandStackController, Parent));
    m_ModuleManager.reset(new CModuleManager(GuiFactory));
    m_ConnectionManager.reset(new CJackConnectionManager());

    m_ConnectionManager->OpenClient("ConnectionMgr");
}

bool CModular1Controller::Create(const string &Type, const string &Name)
{
    return m_ModuleManager->Create(Type, Name);
}

bool CModular1Controller::Remove(const string &Name)
{
    return m_ModuleManager->Remove(Name);
}

bool CModular1Controller::RemoveAll()
{
    return m_ModuleManager->RemoveAll();
}

bool CModular1Controller::Default()
{
    return m_CommandStackController->Default();
}

std::vector<string> CModular1Controller::GetNames() const
{
    return m_ModuleManager->GetNames();
}

std::vector<string> CModular1Controller::GetSupportedTypes() const
{
    return m_ModuleManager->GetSupportedTypes();
}

void CModular1Controller::Capture()
{
    // capture modules (names, types)
    m_ModuleManager->Capture();
    // capture connections
    m_CapturedConnections = ConnectionsToString(*m_ConnectionManager);
    // capture parameters
    m_CommandStackController->ExportToString(m_CapturedParameters);
}

void CModular1Controller::Restore()
{
    // restore captured modules
    m_ModuleManager->Restore();
    // restore captured connections
    StringToConnections(*m_ConnectionManager, m_CapturedConnections);
    // restore captured parameters
    m_CommandStackController->ImportFromString(m_CapturedParameters);
}

void CModular1Controller::Save(const string &Path)
{

}

void CModular1Controller::Load(const string &Path)
{

}
