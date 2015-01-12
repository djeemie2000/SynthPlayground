#include "SlewLimiterModule.h"
#include "SlewLimiterFilter.h"
#include "JackIOManager.h"

CSlewLimiterModule::CSlewLimiterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CSlewLimiterFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CSlewLimiterModule::~CSlewLimiterModule()
{
    Close();
}

std::string CSlewLimiterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CSlewLimiterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CSlewLimiterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CSlewLimiterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CSlewLimiterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CSlewLimiterModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CSlewLimiterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
