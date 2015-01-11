#include "BipolarLimiterModule.h"
#include "BipolarLimiterFilter.h"
#include "JackIOManager.h"

CBipolarLimiterModule::CBipolarLimiterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CBipolarLimiterFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CBipolarLimiterModule::~CBipolarLimiterModule()
{
    Close();
}

std::string CBipolarLimiterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CBipolarLimiterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CBipolarLimiterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CBipolarLimiterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CBipolarLimiterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CBipolarLimiterModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CBipolarLimiterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
