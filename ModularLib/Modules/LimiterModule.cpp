#include "LimiterModule.h"
#include "LimiterFilter.h"
#include "JackIOManager.h"

CLimiterModule::CLimiterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CLimiterFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CLimiterModule::~CLimiterModule()
{
    Close();
}

std::string CLimiterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CLimiterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CLimiterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CLimiterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CLimiterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CLimiterModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CLimiterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
