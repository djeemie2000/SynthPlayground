#include "ScalerModule.h"
#include "ScalerFilter.h"
#include "JackIOManager.h"

CScalerModule::CScalerModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CScalerFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CScalerModule::~CScalerModule()
{
    Close();
}

std::string CScalerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CScalerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CScalerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CScalerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CScalerModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CScalerModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CScalerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
