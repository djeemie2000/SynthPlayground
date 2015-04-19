#include "WebPageModuleParameterVisitor.h"

CWebPageModuleParameterVisitor::CWebPageModuleParameterVisitor()
    : m_Content()
{
}

void CWebPageModuleParameterVisitor::Start()
{
    // TODO clear
    m_Content << "<h3>Parameters</h3>";
    //m_Content << R"(<form action="SetParameters" >)";
    m_Content << R"(<form>)"; // action on page itself
}

void CWebPageModuleParameterVisitor::StartLine()
{
    //m_Content << "<p>";
}

void CWebPageModuleParameterVisitor::FloatParameter(const std::string &ParameterName, const std::string &Name, float Default, float Min, float Max, float Step, int NumDecimals)
{
    m_Content << "<input type=\"number\" name=\"" + ParameterName
              << "\" min=\"" << Min
              << "\" max=\"" << Max
              << "\" step=\"" << Step
              << "\" value=\"" << Default
              << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::IntegerParameter(const std::string &ParameterName, const std::string &Name, int Default, int Min, int Max, int Step)
{
    m_Content << "<input type=\"number\" name=\"" + ParameterName
              << "\" min=\"" << Min
              << "\" max=\"" << Max
              << "\" step=\"" << Step
              << "\" value=\"" << Default
              << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::SelectionParameter(const std::string &ParameterName, const std::string &Name, int Default, const std::vector<std::string> &Selections)
{
//    m_Content << "<form>";
//    m_Content << "<input list=\"items\" name=\"" << ParameterName << "\" value=\"" << Selections[Default] << "\" >";
//    m_Content << "<datalist name=\"items\">";
//    for(const auto& Item : Selections)
//    {
//        m_Content << "<option value=\"" << Item << "\" >" << Item << "</option>";
//    }
//    m_Content << "</datalist>";

    m_Content << "<select name=\"" << ParameterName << "\" value=\"" << Selections[Default] << "\" >";
    for(const auto& Item : Selections)
    {
        m_Content << "<option value=\"" << Item << "\" >" << Item << "</option>";
    }
    m_Content << "</select>" << Name;

//    m_Content << "";
}

void CWebPageModuleParameterVisitor::BooleanParameter(const std::string &ParameterName, const std::string &Name, bool Default)
{
    m_Content << "<input type=\"checkbox\" name=\"" << ParameterName << "\" value=\"" << Default << "\" >" << Name;
}

void CWebPageModuleParameterVisitor::BooleanStatus(const std::string &ParameterName, const std::string &Name, bool Default)
{
    //m_Content += "<input type=\"checkbox\" name=\"" + ParameterName + "\" value=\"" + std::to_string(Default) +"\" >" + Name;
}

void CWebPageModuleParameterVisitor::FinishLine()
{
    m_Content << "<br>"; //"</p>";
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

