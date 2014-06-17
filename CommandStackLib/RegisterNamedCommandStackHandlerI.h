#ifndef REGISTERNAMEDCOMMANDSTACKHANDLERI_H
#define REGISTERNAMEDCOMMANDSTACKHANDLERI_H

#include <string>
#include "CommandStackHandlerI.h"

class IRegisterNamedCommandStackHandler
{
public:
    virtual ~IRegisterNamedCommandStackHandler(){}

    virtual void Register(const std::string& Name, SPCommandStackHandler Handler) =0;
};

#endif // REGISTERNAMEDCOMMANDSTACKHANDLERI_H
