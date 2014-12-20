#ifndef MODULEGUIFACTORY_H
#define MODULEGUIFACTORY_H

#include <memory>
#include <map>
#include <string>
#include "ModuleFactoryI.h"

class QTabWidget;
class CCommandStackController;

class CModuleGuiFactory : public IModuleFactory
{
public:
    CModuleGuiFactory(std::shared_ptr<IModuleFactory> Factory, std::shared_ptr<CCommandStackController> CommandStackController, QTabWidget* Parent);

    std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name) override;
    std::vector<std::string> GetSupportedTypes() const override;

private:
    QTabWidget* m_Parent;
    std::shared_ptr<IModuleFactory> m_Factory;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
};

#endif // MODULEGUIFACTORY_H
