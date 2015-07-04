#include "BinaryOscillatorModule.h"
#include "BinaryOscillatorFilter.h"
#include "JackIOManager.h"

CBinaryOscillatorModule::CBinaryOscillatorModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CBinaryOscillatorFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CBinaryOscillatorModule::~CBinaryOscillatorModule()
{
    Close();
}

std::string CBinaryOscillatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CBinaryOscillatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CBinaryOscillatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CBinaryOscillatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CBinaryOscillatorModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CBinaryOscillatorModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CBinaryOscillatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
