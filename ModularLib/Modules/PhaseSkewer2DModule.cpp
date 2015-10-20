#include "PhaseSkewer2DModule.h"
#include "SkewerFilter2D.h"
#include "JackIOManager.h"

CPhaseSkewer2DModule::CPhaseSkewer2DModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CPhaseSkewer2DFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CPhaseSkewer2DModule::~CPhaseSkewer2DModule()
{
    Close();
}

std::string CPhaseSkewer2DModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPhaseSkewer2DModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPhaseSkewer2DModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPhaseSkewer2DModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPhaseSkewer2DModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CPhaseSkewer2DModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CPhaseSkewer2DModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
