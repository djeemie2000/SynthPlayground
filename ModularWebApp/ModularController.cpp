#include <fstream>
#include "ModularController.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "JackConnectionManager.h"
#include "PatchManager.h"
#include "PatchReader.h"
#include "PatchWriter.h"
#include "CommandStack.h"

CModularController::CModularController(const std::string& PatchDirectory)
    : m_PatchManager(new CPatchManager(PatchDirectory))
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
    m_ModuleManager.reset(new CModuleManager(Factory));
}

CModularController::~CModularController()
{
    RemoveAll();
    m_ModuleManager.reset();
    m_CommandStackController.reset();
    m_ConnectionManager.reset();
}

bool CModularController::Create(const string &Type, const string &Name)
{
    bool RetVal = m_ModuleManager->Create(Type, Name);
    return RetVal;
}

bool CModularController::Remove(const string &Name)
{
    bool RetVal = m_ModuleManager->Remove(Name);
    return RetVal;
}

bool CModularController::RemoveAll()
{
    bool RetVal = m_ModuleManager->RemoveAll();
    return RetVal;
}

bool CModularController::Default()
{
    return m_CommandStackController->Default();
}

void CModularController::Capture()
{
    // capture modules (names, types)
    m_ModuleManager->Capture();
    // capture connections
    m_CapturedConnections = ConnectionsToString(*m_ConnectionManager);
    // capture parameters
    m_CommandStackController->ExportToString(m_CapturedParameters);
}

void CModularController::Restore()
{
    // restore captured modules
    m_ModuleManager->Restore();
    // restore captured connections
    StringToConnections(*m_ConnectionManager, m_CapturedConnections);
    // restore captured parameters
    m_CommandStackController->ImportFromString(m_CapturedParameters);
}

const CModuleManager &CModularController::GetModuleManager() const
{
    return *m_ModuleManager;
}

const CPatchManager &CModularController::GetPatchManager() const
{
    return *m_PatchManager;
}

CCommandStackController &CModularController::GetCommandStackController()
{
    return *m_CommandStackController;
}

bool CModularController::LoadPatch(const string &PatchName)
{
    bool Succeeded = false;
    std::string Path = m_PatchManager->GetPath(PatchName);
    if(!Path.empty())
    {
        Succeeded = Load(Path);
    }
    return Succeeded;

}

bool CModularController::SavePatch(const string &PatchName)
{
    bool Succeeded = false;
    std::string Path = m_PatchManager->CreatePath(PatchName);
    if(!Path.empty())
    {
        Succeeded = Save(Path);
    }
    return Succeeded;
}

bool CModularController::Save(const string &Path)
{
    CPatchWriter Writer;
    return Writer.WritePatch(Path, m_CommandStackController->GetCurrent(), *m_ModuleManager, *m_ConnectionManager);
}

bool CModularController::Load(const string &Path)
{
    CCommandStack ImportedStack;
    CPatchReader Reader;
    return Reader.ReadPatch(Path, ImportedStack, *m_ModuleManager, *m_ConnectionManager)
            && m_CommandStackController->ImportFromStack(ImportedStack);
}
