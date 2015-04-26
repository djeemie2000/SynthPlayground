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
    m_Content << "<h3>Parameters</h3>";
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

    m_Content << "<input list=\"" << ParameterName << "\" name=\"" << ParameterName << "\" value=\"" << Selections[Item.IntValue()] << "\" >";
    m_Content << "<datalist id=\"" << ParameterName <<"\">";
    for(const auto& Selection : Selections)
    {
        m_Content << "<option value=\"" << Selection << "\" >";
    }
    m_Content << "</datalist>";


//    m_Content << "<select name=\"" << ParameterName << "\" value=\"" << Selections[Item.IntValue()] << "\" >";
//    for(const auto& Selection : Selections)
//    {
//        m_Content << "<option value=\"" << Selection << "\" >" << Selection << "</option>";
//    }
//    m_Content << "</select>" << Name;
}

void CWebPageModuleParameterVisitor::BooleanParameter(const std::string &ParameterName, const std::string &Name, bool Default)
{
    SCmdStackItem Item = m_CommandStackController.GetCurrent(ParameterName);

    m_Content << "<input type=\"checkbox\" name=\"" << ParameterName << "\" value=\"" << Item.BoolValue() << "\" >" << Name;
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
    m_Content << R"(<br><input type="submit" value="Submit">)";
    m_Content << "</form>";
}

std::string CWebPageModuleParameterVisitor::GetContent() const
{
    return m_Content.str();
}

