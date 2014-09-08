#include "LinSegOperatorModule.h"
#include "LinSegOperatorFilter.h"
#include "JackIOManager.h"

CLinSegOperatorModule::CLinSegOperatorModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CLinSegOperatorFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CLinSegOperatorModule::~CLinSegOperatorModule()
{
    Close();
}

std::string CLinSegOperatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CLinSegOperatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CLinSegOperatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CLinSegOperatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CLinSegOperatorModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CLinSegOperatorModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CLinSegOperatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
