#include "WebPageModuleParameterVisitor.h"
#include "CommandStackController.h"
#include "CommandStackItem.h"

CWebPageModuleParameterVisitor::CWebPageModuleParameterVisitor(CCommandStackController &CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Content()
{
}

void CWebPageModuleParameterVisitor::Start()
{
    // clear
    m_Content.str("");

    // start
    m_Content << R"(<form>)"; // action on page itself
}

void CWebPageModuleParameterVisitor::StartLine()
{
}

void CWebPageModuleParameterVisitor::FloatParameter(const std::string &ParameterName, const std::string &Name, float Default, float Min, float Max, float Step, int NumDecimals)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<input type=\"number\" name=\"" + ParameterName
              << "\" min=\"" << Min
              << "\" max=\"" << Max
              << "\" step=\"" << Step
              << "\" value=\"" << Item.FloatValue()//Default
              << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::IntegerParameter(const std::string &ParameterName, const std::string &Name, int Default, int Min, int Max, int Step)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<input type=\"number\" name=\"" + ParameterName
              << "\" min=\"" << Min
              << "\" max=\"" << Max
              << "\" step=\"" << Step
              << "\" value=\"" << Item.IntValue()//Default
              << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::SelectionParameter(const std::string &ParameterName, const std::string &Name, int Default, const std::vector<std::string> &Selections)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<select name=\"" << ParameterName << "\" >";
    for(std::size_t idx = 0; idx<Selections.size(); ++idx)
    {
        m_Content << "<option value=\"" << idx << "\" ";
        if(idx == Item.IntValue())
        {
            m_Content << "selected ";
        }
        m_Content << " >" << Selections[idx] << "</option>";
    }
    m_Content << "</select>" << Name;
}

void CWebPageModuleParameterVisitor::BooleanParameter(const std::string &ParameterName, const std::string &Name, bool Default)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<input type=\"checkbox\" name=\"" << ParameterName << "\" value=\"" << Item.BoolValue() << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::FilePathParameter(const string &ParameterName, const string &Name, const string &Extensions)
{
    //TODO
}

void CWebPageModuleParameterVisitor::BooleanStatus(const std::string &ParameterName, const std::string &Name, bool Default)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<input type=\"checkbox\" name=\"" << ParameterName + "\" value=\"" << Item.BoolValue() << "\" >" + Name;
    //TODO??
}

void CWebPageModuleParameterVisitor::FinishLine()
{
    m_Content << "<br>";
}

void CWebPageModuleParameterVisitor::Finish()
{
    m_Content << R"(<br><input type="submit" name="Command" value="Edit">)";
    m_Content << "</form>";
}

std::string CWebPageModuleParameterVisitor::GetContent() const
{
    return m_Content.str();
}

