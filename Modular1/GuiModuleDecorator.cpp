#include "GuiModuleDecorator.h"
#include "CountModuleParameterVisitor.h"
#include <QStackedWidget>

CGuiModuleDecorator::CGuiModuleDecorator(std::shared_ptr<IModularModule> Module,
                                         QStackedWidget *Parent,
                                         QWidget* Widget)
 : m_Module(Module)
 , m_Parent(Parent)
 , m_Widget(Widget)
{
    //only add a tab if there are parameters in the module
    CCountModuleParameterVisitor Visitor;
    m_Module->Accept(Visitor);
    if(0<Visitor.GetParameterCount())
    {
        m_Parent->addWidget(m_Widget);
        m_Parent->setCurrentWidget(m_Widget);//???
    }
}

CGuiModuleDecorator::~CGuiModuleDecorator()
{
    m_Parent->removeWidget(m_Widget);
    delete m_Widget;//ownership of widget here! ?
}

std::string CGuiModuleDecorator::GetName() const
{
    return m_Module ? m_Module->GetName() : "";
}

IModularModule::Names CGuiModuleDecorator::GetInputNames() const
{
    return m_Module ? m_Module->GetInputNames() : Names();
}

IModularModule::Names CGuiModuleDecorator::GetOutputNames() const
{
    return m_Module ? m_Module->GetOutputNames() : Names();
}

IModularModule::Names CGuiModuleDecorator::GetMidiInputNames() const
{
    return m_Module ? m_Module->GetMidiInputNames() : Names();
}

IModularModule::Names CGuiModuleDecorator::GetMidiOutputNames() const
{
    return m_Module ? m_Module->GetMidiOutputNames() : Names();
}

void CGuiModuleDecorator::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    if(m_Module)
    {
        m_Module->Accept(ParameterVisitor);
    }
}
