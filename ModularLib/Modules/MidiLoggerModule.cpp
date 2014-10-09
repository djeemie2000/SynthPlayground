#include "MidiLoggerModule.h"
#include "MidiLoggerFilter.h"
#include "JackIOManager.h"

CMidiLoggerModule::CMidiLoggerModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CMidiLoggerFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CMidiLoggerModule::~CMidiLoggerModule()
{
    Close();
}

std::string CMidiLoggerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMidiLoggerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMidiLoggerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMidiLoggerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMidiLoggerModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CMidiLoggerModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CMidiLoggerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
