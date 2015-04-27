#include "RingSequencerModule.h"
#include "RingSequencerFilter.h"
#include "JackIOManager.h"

CRingSequencerModule::CRingSequencerModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CRingSequencerFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CRingSequencerModule::~CRingSequencerModule()
{
    Close();
}

std::string CRingSequencerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CRingSequencerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CRingSequencerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CRingSequencerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CRingSequencerModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CRingSequencerModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CRingSequencerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
