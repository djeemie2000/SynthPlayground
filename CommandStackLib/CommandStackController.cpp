#include "CommandStackController.h"
#include "ExecuteCommandStackHandler.h"
#include "LogCommandStackHandler.h"
#include "MultiCommandStackHandler.h"
#include "CommandStackImporter.h"
#include "ExportCommandStackHandler.h"
#include "CommandStackDistributor.h"
#include "CommandStack.h"

CCommandStackController::CCommandStackController()
    : m_Logger(new CLogCommandStackHandler())
    , m_Executor(new CExecuteCommandStackHandler())
    , m_Distributor(new CCommandStackDistributor())
    , m_Handler()
    , m_DefaultStack(new CCommandStack())
    , m_CurrentStack(new CCommandStack())
{
    std::shared_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());
    MultiHandler->Register(m_Logger);
    MultiHandler->Register(m_Executor);
    MultiHandler->Register(m_Distributor);
    m_Handler = MultiHandler;
}

bool CCommandStackController::Default()
{
    m_DefaultStack->Apply(*m_Handler);
    return true;
}

void CCommandStackController::Handle(const SCmdStackItem &Item)
{
    m_Handler->Handle(Item);
    m_CurrentStack->AddItem(Item);
}

void CCommandStackController::Register(const string &CommandName, SPCommandStackHandler Handler)
{
    m_Distributor->Register(CommandName, Handler);
}

void CCommandStackController::AddCommand(const SCmdStackItem &Default, CmdFunction Function)
{
    m_Executor->AddCommandFunction(Default.s_Name, Function);
    m_DefaultStack->AddItem(Default);
    m_CurrentStack->AddItem(Default);
}

void CCommandStackController::RemoveCommand(const string &CommandName)
{
    m_Executor->RemoveCommandFunction(CommandName);
    m_DefaultStack->RemoveItem(CommandName);
    m_CurrentStack->RemoveItem(CommandName);
}

bool CCommandStackController::ImportFromString(const string &Content)
{
    // read imported stack from string
    CCommandStackImporter Importer;
    CCommandStack ImportedStack;
    if(Importer.ImportFromString(Content, ImportedStack))
    {
        // if succeeded:
        // reset current stack to default
        *m_CurrentStack = *m_DefaultStack;//?????????????
        // apply imported stack to current stack
        m_CurrentStack->AddItems(ImportedStack);
        // -> now the current stack is up to date with the defaults modified by the imported
        // finally, apply current stack to handler
        m_CurrentStack->Apply(*m_Handler);

        return true;
    }
    return false;
}

bool CCommandStackController::ExportToString(string &Content)
{
    // create Exporter
    CExportCommandStackHandler Exporter;
    // apply current stack to exporter
    m_CurrentStack->Apply(Exporter);
    // exporter exports to string
    return Exporter.ExportToString(Content);
}
