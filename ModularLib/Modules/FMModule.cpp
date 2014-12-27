#include "FMModule.h"
#include "FMFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CFMModule::CFMModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/ModWaveform", false, 3, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SelectModulatorWaveform(Item.s_IntValue); });
    // Open here?
    Open();
}

CFMModule::~CFMModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Resonance");
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
    Close();
}

std::string CFMModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CFMModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CFMModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CFMModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CFMModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/ModWaveform", "Modulator", 3, CSelectableOperatorFactory::SelectionList());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CFMModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CFMFilter( m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CFMModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
