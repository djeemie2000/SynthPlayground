#include "IntFeedbackDelayModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "IntFeedbackDelayFilter.h"
#include "IntOperatorFactory.h"

CIntFeedbackDelayModule::CIntFeedbackDelayModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
}

CIntFeedbackDelayModule::~CIntFeedbackDelayModule()
{
    // remove from command stack
    Close();
}

std::string CIntFeedbackDelayModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntFeedbackDelayModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntFeedbackDelayModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntFeedbackDelayModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntFeedbackDelayModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CIntFeedbackDelayModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntFeedbackDelayFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CIntFeedbackDelayModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
