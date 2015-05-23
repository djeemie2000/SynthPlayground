#include "BasicSamplerModule.h"
#include "BasicSamplerFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CBasicSamplerModule::CBasicSamplerModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
//    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/ModWaveform").IntValue(3), [this](const SCmdStackItem& Item) { m_Filter->SelectModulatorWaveform(Item.s_IntValue); });

    m_Filter->OnLoad("/home/pj/Downloads/musicradar-atmospheric-samples-2/Textures/WaillingBees.wav");//TODO!!!!!!!!!
}

CBasicSamplerModule::~CBasicSamplerModule()
{
    // remove from command stack
//    m_CommandStackController.RemoveCommand(m_Name+"/ModWaveform");
    Close();
}

std::string CBasicSamplerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CBasicSamplerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CBasicSamplerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CBasicSamplerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CBasicSamplerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    //ParameterVisitor.SelectionParameter(m_Name+"/ModWaveform", "Modulator", 3, CSelectableOperatorFactory::SelectionList());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CBasicSamplerModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CBasicSamplerFilter( m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CBasicSamplerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
