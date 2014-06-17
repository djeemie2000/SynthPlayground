#ifndef COMMANDSTACKCONTROLLER_H
#define COMMANDSTACKCONTROLLER_H

#include <memory>
#include "CommandStack.h"

class ICommandStackHandler;
class IExporter;
class IImporter;
class IRegisterNamedCommandStackHandler;

class CCommandStackController
{
public:
    CCommandStackController(const CmdFunctionMap& FunctionMap, const CmdStack& Defaults);
    CCommandStackController(SPCommandStackHandler Executor, const CmdStack& Defaults);


    bool Import(const std::string& Path); //!< load a patch
    bool Default(); //!< apply default settings / patch
    bool Export(const std::string& Path); //!< save current settings/patch

    void Handle(const SCmdStackItem& Item); //!< handle commands

    void Register(const std::string& Name, SPCommandStackHandler Handler); //!< register listeners

private:
    std::shared_ptr<ICommandStackHandler> m_Handler;
    std::shared_ptr<IExporter> m_Exporter;
    std::shared_ptr<IImporter> m_Importer;
    std::shared_ptr<IRegisterNamedCommandStackHandler> m_Register;
};

#endif // COMMANDSTACKCONTROLLER_H
