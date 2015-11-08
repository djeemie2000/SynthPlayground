#include "CombFilterModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "CombFilterFilter.h"

CCombFilterModule::CCombFilterModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
}

CCombFilterModule::~CCombFilterModule()
{
    // remove from command stack
    Close();
}

std::string CCombFilterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CCombFilterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CCombFilterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CCombFilterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CCombFilterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CCombFilterModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CCombFilterFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CCombFilterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
