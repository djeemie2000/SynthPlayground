#include "ModuleGuiParameterVisitor.h"
#include "GuiUtilities.h"
#include <QGridLayout>
#include <QGroupBox>

CGuiModuleParameterVisitor::CGuiModuleParameterVisitor(QGroupBox *GroupBox,
                                                       QWidget *Parent,
                                                       CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_GroupBox(GroupBox)
 , m_Parent(Parent)
 , m_Layout(new QGridLayout())
 , m_Line(0)
 , m_Pos(0)
{
    // assumes groupbox does not have previous layout
    if(m_GroupBox->layout())
    {
        int bs = 0;
    }
    m_GroupBox->setLayout(m_Layout);
}

void CGuiModuleParameterVisitor::Start()
{
}

void CGuiModuleParameterVisitor::StartLine()
{
    m_Pos = 0;
}

void CGuiModuleParameterVisitor::FloatParameter(const std::string &ParameterName, const std::string &Name, float Default, float Min, float Max, float Step, int NumDecimals)
{
    if(!Name.empty())
    {
        guiutils::AddLabel(m_Layout, m_Parent, m_Pos++, m_Line, Name);
    }
    guiutils::AddDoubleSpinBox(m_Layout, m_Parent, m_Pos++, m_Line, {Name, Default, Min, Max, Step, NumDecimals}, ParameterName, m_CommandStackController);
}

void CGuiModuleParameterVisitor::IntegerParameter(const std::string &ParameterName, const std::string &Name, int Default, int Min, int Max, int Step)
{
    if(!Name.empty())
    {
        guiutils::AddLabel(m_Layout, m_Parent, m_Pos++, m_Line, Name);
    }
    guiutils::AddSpinBox(m_Layout, m_Parent, m_Pos++, m_Line, {Name, Default, Min, Max, Step}, ParameterName, m_CommandStackController);
}

void CGuiModuleParameterVisitor::SelectionParameter(const std::string &ParameterName, const std::string &Name, int Default, const std::vector<std::string> &Selections)
{
    if(!Name.empty())
    {
        guiutils::AddLabel(m_Layout, m_Parent, m_Pos++, m_Line, Name);
    }
    guiutils::AddComboBox(m_Layout, m_Parent, m_Pos++, m_Line, {Name, Selections, Default}, ParameterName, m_CommandStackController);
}

void CGuiModuleParameterVisitor::BooleanParameter(const std::string &ParameterName, const std::string &Name, bool Default)
{
    if(!Name.empty())
    {
        guiutils::AddLabel(m_Layout, m_Parent, m_Pos++, m_Line, Name);
    }
    guiutils::AddCheckableSmallButton(m_Layout, m_Parent, m_Pos++, m_Line, Name, ParameterName, Default, m_CommandStackController);
}

void CGuiModuleParameterVisitor::FilePathParameter(const std::string &ParameterName, const std::string &Name, const std::string &Extensions)
{
    //TODO
}

void CGuiModuleParameterVisitor::BooleanStatus(const std::string &ParameterName, const std::string &Name, bool /*Default*/)
{
    if(!Name.empty())
    {
        guiutils::AddLabel(m_Layout, m_Parent, m_Pos++, m_Line, Name);
    }
    guiutils::AddStatusLed(m_Layout, m_Parent, m_Pos++, m_Line, ParameterName, m_CommandStackController);
}

void CGuiModuleParameterVisitor::FinishLine()
{
    ++m_Line;
    m_Pos = 0;
}

void CGuiModuleParameterVisitor::Finish()
{
}
