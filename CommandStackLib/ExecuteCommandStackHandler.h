#ifndef EXECUTECOMMANDSTACKHANDLER_H
#define EXECUTECOMMANDSTACKHANDLER_H

#include <string>
#include "CommandStack.h"
#include "CommandStackHandlerI.h"

class CExecuteCommandStackHandler : public ICommandStackHandler
{
public:
    CExecuteCommandStackHandler(const CmdFunctionMap& FunctionMap);

    void Handle(const SCmdStackItem& Item) override;

    void Add(const std::string& Name, const CmdFunction& Function);
    void Remove(const std::string& Name);

private:
    CmdFunctionMap m_FunctionMap;
};

#endif // EXECUTECOMMANDSTACKHANDLER_H
