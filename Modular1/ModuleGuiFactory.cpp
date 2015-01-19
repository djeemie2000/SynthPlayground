#include "ModuleGuiFactory.h"
#include "ModuleFactoryI.h"
#include "GuiModuleDecorator.h"
#include <QStackedWidget>
#include <QLayout>
#include "QGenericModuleWidget.h"

CGuiModuleFactory::CGuiModuleFactory(std::shared_ptr<IModuleFactory> Factory,
                                     std::shared_ptr<CCommandStackController> CommandStackController,
                                     std::shared_ptr<CJackConnectionManager> ConnectionManager,
                                     QStackedWidget *Parent)
 : m_Parent(Parent)
 , m_Factory(Factory)
 , m_CommandStackController(CommandStackController)
 , m_ConnectionManager(ConnectionManager)
{
}

std::shared_ptr<IModularModule> CGuiModuleFactory::Create(const std::string &Type, const std::string &Name)
{
    if(auto Module = m_Factory->Create(Type, Name))
    {
        QGenericModuleWidget* Widget = new QGenericModuleWidget(Module, *m_CommandStackController, m_Parent);

        return std::shared_ptr<IModularModule>(new CGuiModuleDecorator(Module, m_Parent, Widget));
    }

    return nullptr;
}

std::vector<std::string> CGuiModuleFactory::GetSupportedTypes(const std::string &Category) const
{
    return m_Factory->GetSupportedTypes(Category);
}

std::vector<std::string> CGuiModuleFactory::GetSupportedCategories() const
{
    return m_Factory->GetSupportedCategories();
}

