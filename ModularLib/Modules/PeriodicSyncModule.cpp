#include "PeriodicSyncModule.h"
#include "PeriodicSyncFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"

CPeriodicSyncModule::CPeriodicSyncModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CPeriodicSyncModule::~CPeriodicSyncModule()
{
    Close();
}

std::string CPeriodicSyncModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPeriodicSyncModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPeriodicSyncModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPeriodicSyncModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPeriodicSyncModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CPeriodicSyncModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CPeriodicSyncFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CPeriodicSyncModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
