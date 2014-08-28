#include "GuiModuleDecorator.h"
#include <QMainWindow>
#include <QDockWidget>

CGuiModuleDecorator::CGuiModuleDecorator(std::shared_ptr<IModularModule> Module,
                                         QMainWindow *MainWindow,
                                         QDockWidget *DockWidget)
 : m_Module(Module)
 , m_MainWindow(MainWindow)
 , m_DockWidget(DockWidget)
{
    m_MainWindow->addDockWidget(Qt::TopDockWidgetArea, m_DockWidget);
}

CGuiModuleDecorator::~CGuiModuleDecorator()
{
    m_MainWindow->removeDockWidget(m_DockWidget);
}

std::string CGuiModuleDecorator::GetName() const
{
    return m_Module ? m_Module->GetName() : "";
}
