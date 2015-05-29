#ifndef MODULEGUIFACTORY_H
#define MODULEGUIFACTORY_H

#include <memory>
#include <map>
#include <string>
#include "ModuleFactoryI.h"

class QStackedWidget;
class CCommandStackController;
class CJackConnectionManager;

class CGuiModuleFactory : public IModuleFactory
{
public:
    CGuiModuleFactory(std::shared_ptr<IModuleFactory> Factory,
                      std::shared_ptr<CCommandStackController> CommandStackController,
                      std::shared_ptr<CJackConnectionManager> ConnectionManager,
                      QStackedWidget* Parent);

    std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name) override;
    std::vector<std::string> GetSupportedTypes(const std::string& Category) const override;
    std::vector<std::string> GetSupportedCategories() const override;

private:
    QStackedWidget* m_Parent;
    std::shared_ptr<IModuleFactory> m_Factory;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CJackConnectionManager> m_ConnectionManager;
};

#endif // MODULEGUIFACTORY_H
