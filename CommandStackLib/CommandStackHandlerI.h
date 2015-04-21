#ifndef COMMANDSTACKHANDLERI_H
#define COMMANDSTACKHANDLERI_H

#include <memory>
#include "CommandStackItem.h"

class ICommandStackHandler
{
public:
    virtual ~ICommandStackHandler(){}

    virtual void Handle(const SCmdStackItem& Item) =0;
};

typedef std::shared_ptr<ICommandStackHandler> SPCommandStackHandler;


#endif // COMMANDSTACKHANDLERI_H
