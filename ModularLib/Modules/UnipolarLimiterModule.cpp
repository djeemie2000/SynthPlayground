#include "UnipolarLimiterModule.h"
#include "UnipolarLimiterFilter.h"
#include "JackIOManager.h"

CUnipolarLimiterModule::CUnipolarLimiterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CUnipolarLimiterFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CUnipolarLimiterModule::~CUnipolarLimiterModule()
{
    Close();
}

std::string CUnipolarLimiterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CUnipolarLimiterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CUnipolarLimiterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CUnipolarLimiterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CUnipolarLimiterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CUnipolarLimiterModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CUnipolarLimiterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
