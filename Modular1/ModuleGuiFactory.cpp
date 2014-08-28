#include "ModuleGuiFactory.h"
#include "ModuleFactoryI.h"
#include <QMainWindow>
#include <QDockWidget>
#include <QLayout>
#include "QGenericModuleWidget.h"

CModuleGuiFactory::CModuleGuiFactory(std::shared_ptr<IModuleFactory> Factory, QMainWindow *Parent)
 : m_Parent(Parent)
 , m_Factory(Factory)
 , m_DockWidgets()
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
    m_Parent->addDockWidget(Qt::TopDockWidgetArea, DockWidget);

    // remember dock widget for later removal
    m_DockWidgets[Name] = DockWidget;

    return m_Factory->Create(Type, Name);
}

std::vector<std::string> CModuleGuiFactory::GetSupportedTypes() const
{
    return m_Factory->GetSupportedTypes();
}

void CModuleGuiFactory::Remove(const std::string &Name)
{
    // get dock widget from map of previously created dock widgets
    m_Parent->removeDockWidget(m_DockWidgets[Name]);
    m_DockWidgets.erase(Name);
}
