#ifndef COMMANDSTACKDISTRIBUTOR_H
#define COMMANDSTACKDISTRIBUTOR_H

#include <string>
#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"
#include "RegisterNamedCommandStackHandlerI.h"

class CCommandStackDistributor : public ICommandStackHandler, public IRegisterNamedCommandStackHandler
{
public:
    CCommandStackDistributor();

    void Handle(const SCmdStackItem &Item) override;

    void Register(const std::string& Name, SPCommandStackHandler Handler) override;

private:
    typedef std::map<std::string, SPCommandStackHandler> HandlerMap;
    HandlerMap m_Handlers;
};

#endif // COMMANDSTACKDISTRIBUTOR_H
