#ifndef MODULEFACTORY_H
#define MODULEFACTORY_H

#include <memory>
#include "ModuleFactoryI.h"

class CCommandStackController;

class CModuleFactory : public IModuleFactory
{
public:
    CModuleFactory(std::shared_ptr<CCommandStackController> CommandStackController);

    std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name);
private:
    std::shared_ptr<CCommandStackController> m_CommandStackController;
};

#endif // MODULEFACTORY_H
