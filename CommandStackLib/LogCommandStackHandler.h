#ifndef LOGCOMMANDSTACKHANDLER_H
#define LOGCOMMANDSTACKHANDLER_H

#include "CommandStackHandlerI.h"

class CLogCommandStackHandler : public ICommandStackHandler
{
public:
    CLogCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

};

#endif // LOGCOMMANDSTACKHANDLER_H
