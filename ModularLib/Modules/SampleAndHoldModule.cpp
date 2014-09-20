#include "SampleAndHoldModule.h"
#include "SampleAndHoldFilter.h"
#include "JackIOManager.h"

CSampleAndHoldModule::CSampleAndHoldModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CSampleAndHoldFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CSampleAndHoldModule::~CSampleAndHoldModule()
{
    Close();
}

std::string CSampleAndHoldModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CSampleAndHoldModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CSampleAndHoldModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CSampleAndHoldModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CSampleAndHoldModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CSampleAndHoldModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CSampleAndHoldModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
