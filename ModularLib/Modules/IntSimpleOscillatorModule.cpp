#include "IntSimpleOscillatorModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "IntSimpleOscillatorFilter.h"
#include "IntOperatorFactory.h"

CIntSimpleOscillatorModule::CIntSimpleOscillatorModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Select").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectWaveform(Item.s_IntValue); });
}

CIntSimpleOscillatorModule::~CIntSimpleOscillatorModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Select");
    Close();
}

std::string CIntSimpleOscillatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntSimpleOscillatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntSimpleOscillatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntSimpleOscillatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntSimpleOscillatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/Select", "WaveForm", 0, isl::COperatorFactory<12>::AvailableOperatorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CIntSimpleOscillatorModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntSimpleOscillatorFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CIntSimpleOscillatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
