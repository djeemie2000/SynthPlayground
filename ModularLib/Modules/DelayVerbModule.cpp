#include "DelayVerbModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "DelayVerbFilter.h"

CDelayVerbModule::CDelayVerbModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
}

CDelayVerbModule::~CDelayVerbModule()
{
    // remove from command stack
    Close();
}

std::string CDelayVerbModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CDelayVerbModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CDelayVerbModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CDelayVerbModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CDelayVerbModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CDelayVerbModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CDelayVerbFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CDelayVerbModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
