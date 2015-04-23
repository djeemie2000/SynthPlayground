#include "ToggleGateModule.h"
#include "ToggleGateFilter.h"
#include "JackIOManager.h"

CToggleGateModule::CToggleGateModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CToggleGateFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CToggleGateModule::~CToggleGateModule()
{
    Close();
}

std::string CToggleGateModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CToggleGateModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CToggleGateModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CToggleGateModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CToggleGateModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CToggleGateModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CToggleGateModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
