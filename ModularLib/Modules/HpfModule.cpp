#include "HpfModule.h"
#include "HpfFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CHpfModule::CHpfModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CHpfFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Resonance", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetResonance(Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/Poles", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetPoles(Item.s_IntValue); });
}

CHpfModule::~CHpfModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Resonance");
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
    Close();
}

std::string CHpfModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CHpfModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CHpfModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CHpfModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CHpfModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
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

bool CHpfModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CHpfModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
