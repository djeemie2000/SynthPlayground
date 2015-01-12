#include "OneVoltPerOctaveModule.h"
#include "OneVoltPerOctaveFilter.h"
#include "JackIOManager.h"

COneVoltPerOctaveModule::COneVoltPerOctaveModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new COneVoltPerOctaveFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

COneVoltPerOctaveModule::~COneVoltPerOctaveModule()
{
    Close();
}

std::string COneVoltPerOctaveModule::GetName() const
{
    return m_Name;
}

IModularModule::Names COneVoltPerOctaveModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names COneVoltPerOctaveModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names COneVoltPerOctaveModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void COneVoltPerOctaveModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool COneVoltPerOctaveModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool COneVoltPerOctaveModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
