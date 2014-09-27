#include "PeriodicTriggerModule.h"
#include "PeriodicTriggerFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"

CPeriodicTriggerModule::CPeriodicTriggerModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_Name(Name)
 , m_CommandStackController(CommandStackController)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // commandstack!!
    m_CommandStackController.AddCommand({m_Name+"/BeatsPerMinute", false, 120, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetBeatsPerMinute(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/BeatsPerBar", false, 1, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetBeatsPerBar(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/Duration", false, 100, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetDuration(Item.s_IntValue); });
}

CPeriodicTriggerModule::~CPeriodicTriggerModule()
{
    // commandstack!!
    m_CommandStackController.RemoveCommand(m_Name+"/BeatsPerMinute");
    m_CommandStackController.RemoveCommand(m_Name+"/BeatsPerBar");
    m_CommandStackController.RemoveCommand(m_Name+"/Duration");
    Close();
}

std::string CPeriodicTriggerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPeriodicTriggerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPeriodicTriggerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPeriodicTriggerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPeriodicTriggerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/BeatsPerMinute", "BeatsPerMinute", 120, 1, 240, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/BeatsPerBar", "BeatsPerBar", 1, 1, 16, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/Duration", "Duration", 100, 1, 100, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CPeriodicTriggerModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CPeriodicTriggerFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CPeriodicTriggerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
