#include "ControllerChangeModule.h"
#include "ControllerChangeFilter.h"
#include "JackIOManager.h"

CControllerChangeModule::CControllerChangeModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CControllerChangeFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CControllerChangeModule::~CControllerChangeModule()
{
    Close();
}

std::string CControllerChangeModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CControllerChangeModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CControllerChangeModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CControllerChangeModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CControllerChangeModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CControllerChangeModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CControllerChangeModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
