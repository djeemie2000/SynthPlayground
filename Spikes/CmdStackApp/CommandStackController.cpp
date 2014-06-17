#include "CommandStackController.h"


CCommandStackController::CCommandStackController(const CmdFunctionMap &FunctionMap, const CmdStack &Defaults)
{
    // command stack handling
    std::unique_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());

    MultiHandler->Register(SPCommandStackHandler(new CLogCommandStackHandler()));

    std::shared_ptr<CExportCommandStackHandler> Exporter(new CExportCommandStackHandler());
    MultiHandler->Register(Exporter);

    // app-specific function map
    MultiHandler->Register(SPCommandStackHandler(new CExecuteCommandStackHandler(FunctionMap)));

    // distributor: handles feedback to gui
    std::shared_ptr<CCommandStackDistributor> Distributor(new CCommandStackDistributor());
    MultiHandler->Register(Distributor);

    m_Handler.reset(MultiHandler.release());

    // register
    m_Register = Distributor;

    // exporter (save current patch to file)
    m_Exporter = Exporter;

    // importer (loads a patch from file)
    m_Importer.reset(new CCommandStackImporter(m_Handler, Defaults));
}

CCommandStackController::CCommandStackController(SPCommandStackHandler Executor, const CmdStack &Defaults)
{
    // command stack handling
    std::unique_ptr<CMultiCommandStackHandler> MultiHandler(new CMultiCommandStackHandler());

    MultiHandler->Register(SPCommandStackHandler(new CLogCommandStackHandler()));

    std::shared_ptr<CExportCommandStackHandler> Exporter(new CExportCommandStackHandler());
    MultiHandler->Register(Exporter);

    // app-specific function map
    MultiHandler->Register(Executor);

    // distributor: handles feedback to gui
    std::shared_ptr<CCommandStackDistributor> Distributor(new CCommandStackDistributor());
    MultiHandler->Register(Distributor);

    m_Handler.reset(MultiHandler.release());

    // register
    m_Register = Distributor;

    // exporter (save current patch to file)
    m_Exporter = Exporter;

    // importer (loads a patch from file)
    m_Importer.reset(new CCommandStackImporter(m_Handler, Defaults));
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
    return m_Exporter->Export(Path);
}

void CCommandStackController::Handle(const SCmdStackItem &Item)
{
    m_Handler->Handle(Item);
}

void CCommandStackController::Register(const string &Name, SPCommandStackHandler Handler)
{
    m_Register->Register(Name, Handler);
}
