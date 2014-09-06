#include "CrossMixerModule.h"
#include "CrossMixerFilter.h"
#include "JackIOManager.h"

CCrossMixerModule::CCrossMixerModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CCrossMixerFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CCrossMixerModule::~CCrossMixerModule()
{
    Close();
}

std::string CCrossMixerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CCrossMixerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CCrossMixerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CCrossMixerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CCrossMixerModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CCrossMixerModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CCrossMixerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
