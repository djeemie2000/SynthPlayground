#include "GuiModuleDecorator.h"
#include "CountModuleParameterVisitor.h"
#include <QTabWidget>

CGuiModuleDecorator::CGuiModuleDecorator(std::shared_ptr<IModularModule> Module,
                                         QTabWidget *Parent,
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
        m_Parent->addTab(m_Widget, QString::fromStdString(GetName()));
    }
}

CGuiModuleDecorator::~CGuiModuleDecorator()
{
    int Index = m_Parent->indexOf(m_Widget);
    if(-1!=Index)
    {
        m_Parent->removeTab(Index);
    }
    delete m_Widget;//ownership of widget here!
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

void CGuiModuleDecorator::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    if(m_Module)
    {
        m_Module->Accept(ParameterVisitor);
    }
}
