#include <fstream>
#include "ModularHeadlessController.h"
#include "CommandStackController.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "JackConnectionManager.h"
#include "PatchReader.h"
#include "PatchWriter.h"
#include "CommandStack.h"

CModularHeadlessController::CModularHeadlessController()
 : m_ConnectionManager()
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

CModularHeadlessController::~CModularHeadlessController()
{
    RemoveAll();
    m_ModuleManager.reset();
    m_CommandStackController.reset();
    m_ConnectionManager.reset();
}

bool CModularHeadlessController::RemoveAll()
{
    return m_ModuleManager->RemoveAll();
}

bool CModularHeadlessController::Default()
{
    return m_CommandStackController->Default();
}

bool CModularHeadlessController::Save(const string &Path)
{
    CPatchWriter Writer;
    return Writer.WritePatch(Path, m_CommandStackController->GetCurrent(), *m_ModuleManager, *m_ConnectionManager);
}

bool CModularHeadlessController::Load(const string &Path)
{
    CCommandStack ImportedStack;
    CPatchReader Reader;
    return Reader.ReadPatch(Path, ImportedStack, *m_ModuleManager, *m_ConnectionManager)
            && m_CommandStackController->ImportFromStack(ImportedStack);
}
