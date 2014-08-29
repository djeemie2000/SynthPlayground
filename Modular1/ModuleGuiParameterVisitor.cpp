#include "ModuleGuiParameterVisitor.h"
#include "GuiUtilities.h"

CModuleGuiParameterVisitor::CModuleGuiParameterVisitor(QGroupBox *GroupBox,
                                                       QWidget *Parent,
                                                       CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_GroupBox(GroupBox)
 , m_Parent(Parent)
{
}

void CModuleGuiParameterVisitor::Start()
{
}

void CModuleGuiParameterVisitor::FloatParameter(const std::string &ParameterName, const std::string &Name, float Default, float Min, float Max, float Step, int NumDecimals)
{
    guiutils::AddDoubleSpinBox(m_GroupBox, m_Parent, {Name, Default, Min, Max, Step, NumDecimals}, ParameterName, m_CommandStackController);
}

void CModuleGuiParameterVisitor::SelectionParameter(const std::string &ParameterName, const std::string &Name, int Default, const std::vector<std::string> &Selections)
{
    guiutils::AddComboBox(m_GroupBox, m_Parent, {Name, Selections, Default}, ParameterName, m_CommandStackController);
}

void CModuleGuiParameterVisitor::Finish()
{
}


