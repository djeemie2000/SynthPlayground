#ifndef MODULEGUIFACTORY_H
#define MODULEGUIFACTORY_H

#include <memory>
#include <map>
#include <string>
#include "ModuleFactoryI.h"

class QMainWindow;
class QDockWidget;

class CModuleGuiFactory : public IModuleFactory
{
public:
    CModuleGuiFactory(std::shared_ptr<IModuleFactory> Factory, QMainWindow* Parent);

    std::shared_ptr<IModularModule> Create(const std::string& Type, const std::string& Name) override;
    std::vector<std::string> GetSupportedTypes() const override;

private:
    QMainWindow* m_Parent;
    std::shared_ptr<IModuleFactory> m_Factory;
};

#endif // MODULEGUIFACTORY_H
