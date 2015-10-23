#include "IntSkewer2DModule.h"
#include "IntSkewer2DFilter.h"
#include "JackIOManager.h"

CIntSkewer2DModule::CIntSkewer2DModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CIntSkewer2DFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CIntSkewer2DModule::~CIntSkewer2DModule()
{
    Close();
}

std::string CIntSkewer2DModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntSkewer2DModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntSkewer2DModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntSkewer2DModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntSkewer2DModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CIntSkewer2DModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CIntSkewer2DModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
