#ifndef MODULARMODULEI_H
#define MODULARMODULEI_H

#include <string>

class IModularModule
{
public:
    virtual ~IModularModule(){}

    virtual std::string GetName() const =0;
};

#endif // MODULARMODULEI_H
