#include "DelayLineModule.h"
#include "DelayLineFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CDelayLineModule::CDelayLineModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();

    //defaults
    m_Filter->SetDelayRange(100);

    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/DelayRangeMilliSeconds", true, 100, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetDelayRange(Item.s_IntValue); });
}

CDelayLineModule::~CDelayLineModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/DelayRangeMilliSeconds");
    Close();
}

std::string CDelayLineModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CDelayLineModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CDelayLineModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CDelayLineModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CDelayLineModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/DelayRangeMilliSeconds", "DelayRange(mSec)", 100, 1, m_Filter->GetMaxDelayMilliSeconds(), 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CDelayLineModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CDelayLineFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CDelayLineModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
