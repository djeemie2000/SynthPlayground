#ifndef COMMANDSTACKCONTROLLER_H
#define COMMANDSTACKCONTROLLER_H

#include <memory>
#include "CommandStack.h"
#include "CommandStackHandlerI.h"

class ICommandStackHandler;
class IExporter;
class IImporter;
class IRegisterNamedCommandStackHandler;

class CLogCommandStackHandler;
class CCommandStackImporter;
class CExportCommandStackHandler;
class CCommandStackDistributor;
class CExecuteCommandStackHandler;

class CCommandStackController
{
public:
    CCommandStackController(const CmdFunctionMap& FunctionMap, const CmdStack& Defaults);
    CCommandStackController();

    bool Import(const std::string& Path); //!< load a patch
    bool Default(); //!< apply default settings / patch
    bool Export(const std::string& Path); //!< save current settings/patch
    void Handle(const SCmdStackItem& Item); //!< handle commands
    void Register(const std::string& CommandName, SPCommandStackHandler Handler); //!< register listeners for a specific name
    void AddCommand(const SCmdStackItem& Default, CmdFunction Function);
    void RemoveCommand(const std::string& CommandName);

private:
    std::shared_ptr<CLogCommandStackHandler> m_Logger;
    std::shared_ptr<CExecuteCommandStackHandler> m_Executor;
    std::shared_ptr<CExportCommandStackHandler> m_Exporter;
    std::shared_ptr<CCommandStackDistributor> m_Distributor;
    std::shared_ptr<ICommandStackHandler> m_ImportHandler;
    std::shared_ptr<CCommandStackImporter> m_Importer;
};

#endif // COMMANDSTACKCONTROLLER_H
