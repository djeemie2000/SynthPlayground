#include "UintOscillatorModule.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "UintOscillatorFilter.h"
#include "IntOperatorFactory.h"

CUintOscillatorModule::CUintOscillatorModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CUintOscillatorModule::~CUintOscillatorModule()
{
    Close();
}

std::string CUintOscillatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CUintOscillatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CUintOscillatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CUintOscillatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CUintOscillatorModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CUintOscillatorModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CUintOscillatorFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CUintOscillatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
