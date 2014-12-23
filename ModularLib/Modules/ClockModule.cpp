#include "ClockModule.h"
#include "ClockFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"

CClockModule::CClockModule(const std::string& Name, CCommandStackController &CommandStackController)
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
    m_CommandStackController.AddCommand({m_Name+"/SubDivision", false, 128, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetSubDivision(Item.s_IntValue); });
}

CClockModule::~CClockModule()
{
    // commandstack!!
    m_CommandStackController.RemoveCommand(m_Name+"/BeatsPerMinute");
    m_CommandStackController.RemoveCommand(m_Name+"/BeatsPerBar");
    m_CommandStackController.RemoveCommand(m_Name+"/SubDivision");
    Close();
}

std::string CClockModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CClockModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CClockModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CClockModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CClockModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/BeatsPerMinute", "BeatsPerMinute", 120, 1, 240, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/BeatsPerBar", "BeatsPerBar", 1, 1, 16, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/SubDivision", "SubDivision", 128, 1, 256, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CClockModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CClockFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CClockModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
