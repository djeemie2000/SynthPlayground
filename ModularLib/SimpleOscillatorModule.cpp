#include "SimpleOscillatorModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "SimpleOscillatorFilter.h"

CSimpleOscillatorModule::CSimpleOscillatorModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Select", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SelectWaveform(Item.s_IntValue); });
}

CSimpleOscillatorModule::~CSimpleOscillatorModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Select");
    Close();
}

std::string CSimpleOscillatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CSimpleOscillatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CSimpleOscillatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CSimpleOscillatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CSimpleOscillatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CSimpleOscillatorModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CSimpleOscillatorFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CSimpleOscillatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
