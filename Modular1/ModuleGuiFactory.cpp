#include "ModuleGuiFactory.h"
#include "ModuleFactoryI.h"
#include "GuiModuleDecorator.h"
#include <QTabWidget>
#include <QLayout>
#include "QGenericModuleWidget.h"

CGuiModuleFactory::CGuiModuleFactory(std::shared_ptr<IModuleFactory> Factory,
                                     std::shared_ptr<CCommandStackController> CommandStackController,
                                     QTabWidget *Parent)
 : m_Parent(Parent)
 , m_Factory(Factory)
 , m_CommandStackController(CommandStackController)
{
}

std::shared_ptr<IModularModule> CGuiModuleFactory::Create(const std::string &Type, const std::string &Name)
{
    if(auto Module = m_Factory->Create(Type, Name))
    {
        QGenericModuleWidget* Widget = new QGenericModuleWidget(*Module, *m_CommandStackController, m_Parent);

        return std::shared_ptr<IModularModule>(new CGuiModuleDecorator(Module, m_Parent, Widget));
    }

    return nullptr;
}

std::vector<std::string> CGuiModuleFactory::GetSupportedTypes() const
{
    return m_Factory->GetSupportedTypes();
}

