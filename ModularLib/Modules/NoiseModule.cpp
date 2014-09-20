#include "NoiseModule.h"
#include "NoiseFilter.h"
#include "JackIOManager.h"

CNoiseModule::CNoiseModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CNoiseFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CNoiseModule::~CNoiseModule()
{
    Close();
}

std::string CNoiseModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CNoiseModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CNoiseModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CNoiseModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CNoiseModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CNoiseModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CNoiseModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
