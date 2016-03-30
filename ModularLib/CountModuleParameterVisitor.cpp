#include "CountModuleParameterVisitor.h"

CCountModuleParameterVisitor::CCountModuleParameterVisitor()
 : m_ParameterCount(0)
{
}

void CCountModuleParameterVisitor::Start()
{

}

void CCountModuleParameterVisitor::StartLine()
{

}

void CCountModuleParameterVisitor::FloatParameter(const std::string &/*ParameterName*/, const std::string &/*Name*/, float /*Default*/, float /*Min*/, float /*Max*/, float /*Step*/, int /*NumDecimals*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::IntegerParameter(const std::string &/*ParameterName*/, const std::string &/*Name*/, int /*Default*/, int /*Min*/, int /*Max*/, int /*Step*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::SelectionParameter(const std::string &/*ParameterName*/, const std::string &/*Name*/, int /*Default*/, const std::vector<std::string> &/*Selections*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::BooleanParameter(const std::string &/*ParameterName*/, const std::string &/*Name*/, bool /*Default*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::FilePathParameter(const std::string &/*ParameterName*/, const std::string &/*Name*/, const std::string &/*Extensions*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::BooleanStatus(const std::string &/*ParameterName*/, const std::string &/*Name*/, bool /*Default*/)
{
    ++m_ParameterCount;
}

void CCountModuleParameterVisitor::FinishLine()
{

}

void CCountModuleParameterVisitor::Finish()
{

}

int CCountModuleParameterVisitor::GetParameterCount() const
{
    return m_ParameterCount;
}
