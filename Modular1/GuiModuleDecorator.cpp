#include "GuiModuleDecorator.h"
#include <QMainWindow>
#include <QDockWidget>

CModuleGuiDecorator::CModuleGuiDecorator(std::shared_ptr<IModularModule> Module,
                                         QMainWindow *MainWindow,
                                         QDockWidget *DockWidget)
 : m_Module(Module)
 , m_MainWindow(MainWindow)
 , m_DockWidget(DockWidget)
{
    m_MainWindow->addDockWidget(Qt::LeftDockWidgetArea, m_DockWidget);
}

CModuleGuiDecorator::~CModuleGuiDecorator()
{
    m_MainWindow->removeDockWidget(m_DockWidget);
}

std::string CModuleGuiDecorator::GetName() const
{
    return m_Module ? m_Module->GetName() : "";
}

IModularModule::Names CModuleGuiDecorator::GetInputNames() const
{
    return m_Module ? m_Module->GetInputNames() : Names();
}

IModularModule::Names CModuleGuiDecorator::GetOutputNames() const
{
    return m_Module ? m_Module->GetOutputNames() : Names();
}

IModularModule::Names CModuleGuiDecorator::GetMidiInputNames() const
{
    return m_Module ? m_Module->GetMidiInputNames() : Names();
}
