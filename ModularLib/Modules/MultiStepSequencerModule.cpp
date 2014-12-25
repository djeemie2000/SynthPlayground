#include "MultiStepSequencerModule.h"
#include "MultiStepSequencerFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"

CMultiStepSequencerModule::CMultiStepSequencerModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_Name(Name)
 , m_CommandStackController(CommandStackController)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
 , m_CurrentStep(0)
{
    // Open here?
    Open();
    // commandstack!!
    int MaxNumSteps = CMultiStepSequencerFilter::NumSequencerSteps;
    m_CommandStackController.AddCommand({m_Name+"/IsActive", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetActive(Item.s_BoolValue); });
    m_CommandStackController.AddCommand({m_Name+"/StepIntervalLength", false, MaxNumSteps, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetStepIntervalLength(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/StepSize", false, 1, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetStepSize(Item.s_IntValue); });
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Mode", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetStepMode(idx, Item.s_IntValue); });
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Octave", false, 3, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetOctave(idx, static_cast<EOctave>(Item.s_IntValue)); });
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Note", false, static_cast<int>(ENote::A), 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetNote(idx, static_cast<ENote>(Item.s_IntValue)); });
    }

}

CMultiStepSequencerModule::~CMultiStepSequencerModule()
{
    // TODO remove from commandstack!!
    Close();
}

std::string CMultiStepSequencerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMultiStepSequencerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMultiStepSequencerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMultiStepSequencerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMultiStepSequencerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    int MaxNumSteps = CMultiStepSequencerFilter::NumSequencerSteps;
    ParameterVisitor.Start();

    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/IsActive", "Go", false);
    ParameterVisitor.IntegerParameter(m_Name+"/BeginStep", "Begin", 1, 1, MaxNumSteps-1, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/NumSteps", "#Steps", MaxNumSteps, 1, MaxNumSteps, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/StepSize", "Step", 1, 1, MaxNumSteps, 1);
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.IntegerParameter(m_Name+"/Step/"+std::to_string(idx)+"/Velocity", (idx==0? "Vel" : ""), 92, 0, 127, 1);
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.IntegerParameter(m_Name+"/Step/"+std::to_string(idx)+"/Duration", (idx == 0 ? "Dur" : ""), 92, 1, 127, 1);
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.SelectionParameter(m_Name+"/Step/"+std::to_string(idx)+"/RepeatMode", (idx==0 ? "RMode" : ""), 0, { "----", "-_-_", "-___"});
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.IntegerParameter(m_Name+"/Step/"+std::to_string(idx)+"/RepeatValue", (idx == 0 ? "R/L" : ""), 1, 1, 16, 1);
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.SelectionParameter(m_Name+"/Step/"+std::to_string(idx)+"/Note", (idx == 0 ? "Note" : ""), static_cast<int>(ENote::A), { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" });
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.IntegerParameter(m_Name+"/Step/"+std::to_string(idx)+"/Octave", (idx == 0 ? "Oct" : ""), 3, 0, 8, 1);
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.SelectionParameter(m_Name+"/Step/"+std::to_string(idx)+"/Mode", (idx == 0 ? "Mode" : ""), 0, { "Off", "On", "Skip"});
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.StartLine();
    for(int idx = 0; idx<MaxNumSteps; ++idx)
    {
        ParameterVisitor.BooleanStatus(m_Name+"/Step/"+std::to_string(idx)+"/Status", (idx == 0 ? "Curr" : ""), false);
    }
    ParameterVisitor.FinishLine();

    ParameterVisitor.Finish();
}

bool CMultiStepSequencerModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CMultiStepSequencerFilter(m_IOManager->SamplingFrequency(), [this](int Index){ SetCurrentStepIndex(Index);} ));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CMultiStepSequencerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

void CMultiStepSequencerModule::SetCurrentStepIndex(int Index)
{
    // switch off previous step
    m_CommandStackController.Handle({m_Name+"/Step/"+std::to_string(m_CurrentStep)+"/Status", false, 0, 0.0f});
    // switch on current step
    m_CurrentStep = Index;
    m_CommandStackController.Handle({m_Name+"/Step/"+std::to_string(m_CurrentStep)+"/Status", true, 0, 0.0f});
}
