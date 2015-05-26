#include "CommandStackController.h"
#include "ExecuteCommandStackHandler.h"
#include "LogCommandStackHandler.h"
#include "MultiCommandStackHandler.h"
#include "CommandStackImporter.h"
#include "ExportCommandStackHandler.h"
#include "CommandStackDistributor.h"
#include "CommandStack.h"
#include "StackCommandStackHandler.h"

CCommandStackController::CCommandStackController()
    : m_Logger(new CLogCommandStackHandler())
    , m_Executor(new CExecuteCommandStackHandler())
    , m_Distributor(new CCommandStackDistributor())
    , m_Handler()
    , m_DefaultStack(new CCommandStack())
    , m_CurrentStack(new CCommandStack())
{
    std::shared_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());
    MultiHandler->Register(SPCommandStackHandler(new CStackCommandStackHandler(m_CurrentStack)));
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
}

SCmdStackItem CCommandStackController::GetCurrent(const string &CommandName) const
{
    return m_CurrentStack->GetItem(CommandName);
}

const CCommandStack &CCommandStackController::GetCurrent() const
{
    return *m_CurrentStack;
}

void CCommandStackController::Register(const string &CommandName, SPCommandStackHandler Handler)
{
    m_Distributor->Register(CommandName, Handler);
}

void CCommandStackController::AddCommand(const SCmdStackItem &Default, CmdFunction Function)
{
    m_Executor->AddCommandFunction(Default.s_Name, Function);
    m_DefaultStack->AddItem(Default);
    //m_Handler->Handle(Default);
    m_CurrentStack->AddItem(Default);// ??? or: apply added command default
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
    if(Importer.ImportFromString(Content, *m_DefaultStack, ImportedStack))
    { // if succeeded:
        // clear current stack
        m_CurrentStack->Clear();
        // apply defaults (includes applying default to current stack)
        m_DefaultStack->Apply(*m_Handler);
        // apply imported stack (includes applying to current stack)
        ImportedStack.Apply(*m_Handler);

        return true;
    }
    return false;
}

bool CCommandStackController::ImportFromStack(const CCommandStack &ImportedStack)
{
    // clear current stack
    m_CurrentStack->Clear();
    // apply defaults (includes applying default to current stack)
    m_DefaultStack->Apply(*m_Handler);
    // apply imported stack (includes applying to current stack)
    ImportedStack.Apply(*m_Handler);

    return true;
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
