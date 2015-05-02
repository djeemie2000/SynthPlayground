#include "StepSequencerModule.h"
#include "StepSequencerFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"

CStepSequencerModule::CStepSequencerModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_Name(Name)
 , m_CommandStackController(CommandStackController)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
 , m_CurrentStep(0)
{
    // Open here?
    Open();
    // commandstack!!
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/IsActive").BoolValue(false), [this](const SCmdStackItem& Item) { m_Filter->SetActive(Item.s_BoolValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/NumSteps").IntValue(CStepSequencerFilter::NumSequencerSteps), [this](const SCmdStackItem& Item) { m_Filter->SetNumSteps(Item.s_IntValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/StepSize").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetStepSize(Item.s_IntValue); });
    for(int idx = 0; idx<CStepSequencerFilter::NumSequencerSteps; ++idx)
    {
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Step/"+std::to_string(idx)+"/Active").BoolValue(false), [idx,this](const SCmdStackItem& Item) { m_Filter->SetActive(idx, Item.s_BoolValue); });
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Step/"+std::to_string(idx)+"/Octave").IntValue(3), [idx,this](const SCmdStackItem& Item) { m_Filter->SetOctave(idx, static_cast<EOctave>(Item.s_IntValue)); });
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Step/"+std::to_string(idx)+"/Note").IntValue(static_cast<int>(ENote::A)), [idx,this](const SCmdStackItem& Item) { m_Filter->SetNote(idx, static_cast<ENote>(Item.s_IntValue)); });
    }
}

CStepSequencerModule::~CStepSequencerModule()
{
    // TODO commandstack!!
    Close();
}

std::string CStepSequencerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CStepSequencerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CStepSequencerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CStepSequencerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CStepSequencerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    int MaxNumSteps = CStepSequencerFilter::NumSequencerSteps;
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/IsActive", "Go", false);
    ParameterVisitor.IntegerParameter(m_Name+"/NumSteps", "#Steps", CStepSequencerFilter::NumSequencerSteps, 1, CStepSequencerFilter::NumSequencerSteps, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/StepSize", "Step", 1, 1, CStepSequencerFilter::NumSequencerSteps, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.IntegerParameter(m_Name+"/Step/"+std::to_string(idx)+"/Octave", "", 3, 0, 8, 1);
    }
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.SelectionParameter(m_Name+"/Step/"+std::to_string(idx)+"/Note", "", static_cast<int>(ENote::A), { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" });
    }
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.BooleanParameter(m_Name+"/Step/"+std::to_string(idx)+"/Active", "On", false);
    }
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.BooleanStatus(m_Name+"/Step/"+std::to_string(idx)+"/Status", "", false);
    }
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CStepSequencerModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CStepSequencerFilter(m_IOManager->SamplingFrequency(), [this](int Index){ SetCurrentStepIndex(Index);} ));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CStepSequencerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

void CStepSequencerModule::SetCurrentStepIndex(int Index)
{
    // switch off previous step
    m_CommandStackController.Handle(SCmdStackItem(m_Name+"/Step/"+std::to_string(m_CurrentStep)+"/Status").BoolValue(false));
    // switch on current step
    m_CurrentStep = Index;
    m_CommandStackController.Handle(SCmdStackItem(m_Name+"/Step/"+std::to_string(m_CurrentStep)+"/Status").BoolValue(true));
}
