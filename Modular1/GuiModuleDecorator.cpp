#include "GuiModuleDecorator.h"
#include <QTabWidget>

CModuleGuiDecorator::CModuleGuiDecorator(std::shared_ptr<IModularModule> Module,
                                         QTabWidget *Parent,
                                         QWidget* Widget)
 : m_Module(Module)
 , m_Parent(Parent)
 , m_Widget(Widget)
{
    m_Parent->addTab(m_Widget, QString::fromStdString(GetName()));
}

CModuleGuiDecorator::~CModuleGuiDecorator()
{
    m_Parent->removeTab(m_Parent->indexOf(m_Widget));
    delete m_Widget;//ownership of widget here!
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

void CModuleGuiDecorator::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    if(m_Module)
    {
        m_Module->Accept(ParameterVisitor);
    }
}
