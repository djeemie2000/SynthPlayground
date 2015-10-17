#include "ChebishevModule.h"
#include "ChebishevFilter.h"
#include "JackIOManager.h"

CChebishevModule::CChebishevModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CChebishevFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CChebishevModule::~CChebishevModule()
{
    Close();
}

std::string CChebishevModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CChebishevModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CChebishevModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CChebishevModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CChebishevModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CChebishevModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CChebishevModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
