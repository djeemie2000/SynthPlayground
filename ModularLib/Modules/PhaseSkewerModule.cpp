#include "PhaseSkewerModule.h"
#include "SkewerFilter.h"
#include "JackIOManager.h"

CPhaseSkewerModule::CPhaseSkewerModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CPhaseSkewerFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CPhaseSkewerModule::~CPhaseSkewerModule()
{
    Close();
}

std::string CPhaseSkewerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPhaseSkewerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPhaseSkewerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPhaseSkewerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPhaseSkewerModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CPhaseSkewerModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CPhaseSkewerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
