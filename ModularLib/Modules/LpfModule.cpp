#include "LpfModule.h"
#include "LpfModule.h"
#include "LpfFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CLpfModule::CLpfModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CLpfFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Resonance").FloatValue(0.0f), [this](const SCmdStackItem& Item) { m_Filter->SetResonance(Item.s_FloatValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Poles").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetPoles(Item.s_IntValue); });
}

CLpfModule::~CLpfModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Resonance");
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
    Close();
}

std::string CLpfModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CLpfModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CLpfModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CLpfModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CLpfModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/Resonance", "Resonance", 0.0f, 0.0f, 2.0f, 0.01, 3);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/Poles", "Poles", 1, 1, 24, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CLpfModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CLpfModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
