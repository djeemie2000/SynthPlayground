#ifndef MODULEFACTORYI_H
#define MODULEFACTORYI_H

#include <string>
#include <memory>

class IModularModule;

class IModuleFactory
{
public:
    virtual ~IModuleFactory(){}

    virtual std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name) =0;
};

#endif // MODULEFACTORYI_H
