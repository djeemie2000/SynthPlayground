#include "DecayEnvelopeModule.h"
#include "DecayEnvelopeFilter.h"
#include "JackIOManager.h"

CDecayEnvelopeModule::CDecayEnvelopeModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CDecayEnvelopeFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CDecayEnvelopeModule::~CDecayEnvelopeModule()
{
    Close();
}

std::string CDecayEnvelopeModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CDecayEnvelopeModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CDecayEnvelopeModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CDecayEnvelopeModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CDecayEnvelopeModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CDecayEnvelopeModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CDecayEnvelopeModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
