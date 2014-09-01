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
{
    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    std::shared_ptr<CModuleGuiFactory> GuiFactory(new CModuleGuiFactory(Factory, m_CommandStackController, Parent));
    m_ModuleManager.reset(new CModuleManager(GuiFactory));
    m_ConnectionManager.reset(new CJackConnectionManager());
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
    m_ModuleManager->Capture();
    // capture connections
    m_CapturedConnections = ConnectionsToString(*m_ConnectionManager);
    // TODO capture parameters
}

void CModular1Controller::Restore()
{
    m_ModuleManager->Restore();
    // restore connections
    StringToConnections(*m_ConnectionManager, m_CapturedConnections);
    // TODO restore parameters
}

void CModular1Controller::Save(const string &Path)
{

}

void CModular1Controller::Load(const string &Path)
{

}
