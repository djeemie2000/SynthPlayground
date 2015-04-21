#ifndef EXECUTECOMMANDSTACKHANDLER_H
#define EXECUTECOMMANDSTACKHANDLER_H

#include <string>
#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"

class CExecuteCommandStackHandler : public ICommandStackHandler
{
public:
    CExecuteCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    void AddCommandFunction(const std::string& Name, const CmdFunction& Function);
    void RemoveCommandFunction(const std::string& Name);

private:
    CmdFunctionMap m_FunctionMap;
};

#endif // EXECUTECOMMANDSTACKHANDLER_H
