#include <fstream>
#include "Modular1Controller.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "ModuleGuiFactory.h"
#include "JackConnectionManager.h"
#include "tinyxml2.h"
#include "PatchReader.h"
#include "PatchWriter.h"
#include "CommandStack.h"
#include <QStackedWidget>

CModular1Controller::CModular1Controller(QStackedWidget *Parent)
 : m_Parent(Parent)
 , m_ConnectionManager()
 , m_CommandStackController()
 , m_ModuleManager()
 , m_CapturedConnections()
 , m_CapturedParameters()
{
    m_ConnectionManager.reset(new CJackConnectionManager());
    m_ConnectionManager->OpenClient("ConnectionMgr");

    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    std::shared_ptr<CGuiModuleFactory> GuiFactory(new CGuiModuleFactory(Factory, m_CommandStackController, m_ConnectionManager, Parent));
    m_ModuleManager.reset(new CModuleManager(GuiFactory));
}

CModular1Controller::~CModular1Controller()
{
    RemoveAll();
    m_ModuleManager.reset();
    m_CommandStackController.reset();
    m_ConnectionManager.reset();
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

std::vector<string> CModular1Controller::GetSupportedTypes(const std::string& Category) const
{
    return m_ModuleManager->GetSupportedTypes(Category);
}

std::vector<string> CModular1Controller::GetSupportedCategories() const
{
    return m_ModuleManager->GetSupportedCategories();
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

bool CModular1Controller::Save(const string &Path)
{
    CPatchWriter Writer;
    return Writer.WritePatch(Path, m_CommandStackController->GetCurrent(), *m_ModuleManager, *m_ConnectionManager);
}

bool CModular1Controller::Load(const string &Path)
{
    CCommandStack ImportedStack;
    CPatchReader Reader;
    return Reader.ReadPatch(Path, ImportedStack, *m_ModuleManager, *m_ConnectionManager)
            && m_CommandStackController->ImportFromStack(ImportedStack);
}

bool CModular1Controller::Show(const string &Name)
{
    bool Shown = false;
    if(m_Parent)
    {
        for(int index = 0; !Shown && index<m_Parent->count(); ++index)
        {
            Shown = (QString::fromStdString(Name) == m_Parent->widget(index)->windowTitle());
            if(Shown)
            {
                m_Parent->setCurrentIndex(index);
            }
        }
    }
    return Shown;
}
