#include "ModuleGuiFactory.h"
#include "ModuleFactoryI.h"
#include "GuiModuleDecorator.h"
#include <QMainWindow>
#include <QDockWidget>
#include <QLayout>
#include "QGenericModuleWidget.h"

CModuleGuiFactory::CModuleGuiFactory(std::shared_ptr<IModuleFactory> Factory, QMainWindow *Parent)
 : m_Parent(Parent)
 , m_Factory(Factory)
{
}

std::shared_ptr<IModularModule> CModuleGuiFactory::Create(const std::string &Type, const std::string &Name)
{
    // add dockwidget with name to parent
    QGenericModuleWidget* Widget = new QGenericModuleWidget(m_Parent);

    QDockWidget* DockWidget = new QDockWidget(QString::fromStdString(Name), m_Parent);
    DockWidget->setFeatures(QDockWidget::DockWidgetMovable);//not closable, not floatable
    DockWidget->setWidget(Widget);
    // TODO set actual widget in dockwidget
    // TODO generic vs custom?
    // TODO inputs and outputs?
    // TODO generic from parameters
//    m_Parent->addDockWidget(Qt::TopDockWidgetArea, DockWidget);

    return std::shared_ptr<IModularModule>(new CGuiModuleDecorator(m_Factory->Create(Type, Name), m_Parent, DockWidget));
}

std::vector<std::string> CModuleGuiFactory::GetSupportedTypes() const
{
    return m_Factory->GetSupportedTypes();
}
