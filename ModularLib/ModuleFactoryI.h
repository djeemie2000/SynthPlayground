#ifndef MODULEFACTORYI_H
#define MODULEFACTORYI_H

#include <string>
#include <memory>
#include <vector>

class IModularModule;

class IModuleFactory
{
public:
    virtual ~IModuleFactory(){}

    virtual std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name) =0;
    virtual std::vector<std::string> GetSupportedTypes(const std::string& Category) const =0;
    virtual std::vector<std::string> GetSupportedCategories() const =0;
};

#endif // MODULEFACTORYI_H
