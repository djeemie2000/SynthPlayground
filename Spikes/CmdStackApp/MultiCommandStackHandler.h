#ifndef MULTICOMMANDSTACKHANDLER_H
#define MULTICOMMANDSTACKHANDLER_H

#include <vector>
#include "CommandStackHandlerI.h"

class CMultiCommandStackHandler : public ICommandStackHandler
{
public:
    CMultiCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    void Register(SPCommandStackHandler Handler);

private:
    typedef std::vector<SPCommandStackHandler> HandlerList;
    HandlerList m_Handlers;
};

#endif // MULTICOMMANDSTACKHANDLER_H
