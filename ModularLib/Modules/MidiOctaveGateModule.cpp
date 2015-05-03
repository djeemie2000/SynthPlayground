#include "MidiOctaveGateModule.h"
#include "MidiOctaveGateFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CMidiOctaveGateModule::CMidiOctaveGateModule(const std::string& Name, CCommandStackController& CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Name(Name)
    , m_Filter(new CMidiOctaveGateFilter())
    , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Octave").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SetOctave(Item.IntValue()); });
}

CMidiOctaveGateModule::~CMidiOctaveGateModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Octave");
    //
    Close();
}

std::string CMidiOctaveGateModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMidiOctaveGateModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMidiOctaveGateModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMidiOctaveGateModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMidiOctaveGateModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/Octave", "Octave", 0, -1, 8, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CMidiOctaveGateModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CMidiOctaveGateModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
