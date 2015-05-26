#ifndef COMMANDSTACKCONTROLLER_H
#define COMMANDSTACKCONTROLLER_H

#include <memory>
#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"

class ICommandStackHandler;
class IRegisterNamedCommandStackHandler;

class CLogCommandStackHandler;
class CCommandStackDistributor;
class CExecuteCommandStackHandler;
class CCommandStack;

class CCommandStackController
{
public:
    CCommandStackController();

    void AddCommand(const SCmdStackItem& Default, CmdFunction Function);
    void RemoveCommand(const std::string& CommandName);

    void Register(const std::string& CommandName, SPCommandStackHandler Handler); //!< register listeners for a specific name

    bool ImportFromString(const std::string& Content);
    bool ImportFromStack(const CCommandStack& ImportedStack);
    bool ExportToString(std::string& Content);

    bool Default(); //!< apply default settings / patch

    void Handle(const SCmdStackItem& Item); //!< handle commands

    SCmdStackItem GetCurrent(const std::string& CommandName) const;

    const CCommandStack& GetCurrent() const;

private:
    std::shared_ptr<CLogCommandStackHandler> m_Logger;
    std::shared_ptr<CExecuteCommandStackHandler> m_Executor;
    std::shared_ptr<CCommandStackDistributor> m_Distributor;
    std::shared_ptr<ICommandStackHandler> m_Handler;
    std::shared_ptr<CCommandStack> m_DefaultStack;
    std::shared_ptr<CCommandStack> m_CurrentStack;
};

#endif // COMMANDSTACKCONTROLLER_H
