#include "WaveShaperA116Module.h"
#include "WaveShaperA116Filter.h"
#include "JackIOManager.h"

CWaveShaperA116Module::CWaveShaperA116Module(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CWaveShaperA116Filter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CWaveShaperA116Module::~CWaveShaperA116Module()
{
    Close();
}

std::string CWaveShaperA116Module::GetName() const
{
    return m_Name;
}

IModularModule::Names CWaveShaperA116Module::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CWaveShaperA116Module::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CWaveShaperA116Module::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CWaveShaperA116Module::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CWaveShaperA116Module::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CWaveShaperA116Module::Close()
{
    m_IOManager->CloseClient();
    return true;
}
