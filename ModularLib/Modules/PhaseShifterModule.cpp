#include "PhaseShifterModule.h"
#include "PhaseShifterFilter.h"
#include "JackIOManager.h"

CPhaseShifterModule::CPhaseShifterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CPhaseShifterFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CPhaseShifterModule::~CPhaseShifterModule()
{
    Close();
}

std::string CPhaseShifterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPhaseShifterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPhaseShifterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPhaseShifterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPhaseShifterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CPhaseShifterModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CPhaseShifterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
