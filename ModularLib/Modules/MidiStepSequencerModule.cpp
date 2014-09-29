#include "MidiStepSequencerModule.h"
#include "MidiStepSequencerFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"

CMidiStepSequencerModule::CMidiStepSequencerModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_Name(Name)
 , m_CommandStackController(CommandStackController)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // commandstack!!
    m_CommandStackController.AddCommand({m_Name+"/IsActive", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetActive(Item.s_BoolValue); });
    m_CommandStackController.AddCommand({m_Name+"/NumSteps", false, 16, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetNumSteps(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/StepSize", false, 1, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetStepSize(Item.s_IntValue); });
    for(int idx = 0; idx<16; ++idx)
    {
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Active", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetActive(idx, Item.s_BoolValue); });
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Octave", false, 3, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetOctave(idx, static_cast<EOctave>(Item.s_IntValue)); });
        m_CommandStackController.AddCommand({m_Name+"/Step/"+std::to_string(idx)+"/Note", false, static_cast<int>(ENote::A), 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetNote(idx, static_cast<ENote>(Item.s_IntValue)); });
    }

}

CMidiStepSequencerModule::~CMidiStepSequencerModule()
{
    // TODO commandstack!!!!!!!!!!!!!
    Close();
}

std::string CMidiStepSequencerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMidiStepSequencerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMidiStepSequencerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMidiStepSequencerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMidiStepSequencerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    int MaxNumSteps = 16;//TODO from filter?
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/IsActive", "Go", false);
    ParameterVisitor.IntegerParameter(m_Name+"/NumSteps", "#Steps", 16, 1, 16, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/StepSize", "Step", 1, 1, 16, 1);
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
    ParameterVisitor.Finish();
}

bool CMidiStepSequencerModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CMidiStepSequencerFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CMidiStepSequencerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
