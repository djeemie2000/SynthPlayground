#include "CommandStackController.h"
#include "ExecuteCommandStackHandler.h"
#include "LogCommandStackHandler.h"
#include "MultiCommandStackHandler.h"
#include "CommandStackImporter.h"
#include "ExportCommandStackHandler.h"
#include "CommandStackDistributor.h"

CCommandStackController::CCommandStackController(const CmdFunctionMap &FunctionMap, const CmdStack &Defaults)
 : m_Logger(new CLogCommandStackHandler())
 , m_Executor(new CExecuteCommandStackHandler(FunctionMap))
 , m_Exporter(new CExportCommandStackHandler())
 , m_Distributor(new CCommandStackDistributor())
 , m_Handler()
 , m_Importer()
{
    std::shared_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());
    MultiHandler->Register(m_Logger);
    MultiHandler->Register(m_Exporter);
    MultiHandler->Register(m_Executor);
    MultiHandler->Register(m_Distributor);
    m_Handler = MultiHandler;

    // importer (loads a patch from file)
    m_Importer.reset(new CCommandStackImporter(m_Handler, Defaults));
}

CCommandStackController::CCommandStackController()
    : m_Logger(new CLogCommandStackHandler())
    , m_Executor(new CExecuteCommandStackHandler(CmdFunctionMap()))
    , m_Exporter(new CExportCommandStackHandler())
    , m_Distributor(new CCommandStackDistributor())
    , m_Handler()
    , m_Importer()
{
    std::shared_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());
    MultiHandler->Register(m_Logger);
    MultiHandler->Register(m_Exporter);
    MultiHandler->Register(m_Executor);
    MultiHandler->Register(m_Distributor);
    m_Handler = MultiHandler;

    // importer (loads a patch from file)
    m_Importer.reset(new CCommandStackImporter(m_Handler, CmdStack()));
}

bool CCommandStackController::Import(const string &Path)
{
    return m_Importer->Import(Path);
}

bool CCommandStackController::Default()
{
    return m_Importer->Default();
}

bool CCommandStackController::Export(const string &Path)
{
    return m_Exporter->ExportToFile(Path);
}

void CCommandStackController::Handle(const SCmdStackItem &Item)
{
    m_Handler->Handle(Item);
}

void CCommandStackController::Register(const string &CommandName, SPCommandStackHandler Handler)
{
    m_Distributor->Register(CommandName, Handler);
}

void CCommandStackController::AddCommand(const SCmdStackItem &Default, CmdFunction Function)
{
    m_Importer->AddDefault(Default);
    m_Executor->Add(Default.s_Name, Function);
}

void CCommandStackController::RemoveCommand(const string &CommandName)
{
    m_Importer->RemoveDefault(CommandName);
    m_Executor->Remove(CommandName);
}

bool CCommandStackController::ImportFromString(const string &Content)
{
    return m_Importer->ImportFromString(Content);
}

bool CCommandStackController::ExportToString(string &Content)
{
    return m_Exporter->ExportToString(Content);
}
