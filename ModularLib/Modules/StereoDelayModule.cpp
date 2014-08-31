#include "StereoDelayModule.h"
#include "StereoDelayFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CStereoDelayModule::CStereoDelayModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();

    //defaults
    m_Filter->OnDelayBypass(0, true);
    m_Filter->OnDelayBypass(1, true);
    m_Filter->OnDelayMilliSeconds(0, 247.0f);
    m_Filter->OnDelayMilliSeconds(1, 253.0f);
    m_Filter->OnDelayWetDry(0, 0.4f);
    m_Filter->OnDelayWetDry(1, 0.4f);
    m_Filter->OnDelayFeedback(0, 0.5f);
    m_Filter->OnDelayFeedback(1, 0.5f);

    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Left/Bypass", true, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayBypass(0, Item.s_BoolValue); });
    m_CommandStackController.AddCommand({m_Name+"/Left/WetDry", false, 0, 0.4f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayWetDry(0, Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/Left/Feedback", false, 0, 0.5f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayFeedback(0, Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/Left/DelayMilliSeconds", false, 0, 247.0f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayMilliSeconds(0, Item.s_FloatValue); });

    m_CommandStackController.AddCommand({m_Name+"/Right/Bypass", true, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayBypass(1, Item.s_BoolValue); });
    m_CommandStackController.AddCommand({m_Name+"/Right/WetDry", false, 0, 0.4f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayWetDry(1, Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/Right/Feedback", false, 0, 0.5f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayFeedback(1, Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/Right/DelayMilliSeconds", false, 0, 253.0f}, [this](const SCmdStackItem& Item) { m_Filter->OnDelayMilliSeconds(1, Item.s_FloatValue); });
}

CStereoDelayModule::~CStereoDelayModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Left/Bypass");
    m_CommandStackController.RemoveCommand(m_Name+"/Left/WetDry");
    m_CommandStackController.RemoveCommand(m_Name+"/Left/Feedback");
    m_CommandStackController.RemoveCommand(m_Name+"/Left/DelayMilliSeconds");
    m_CommandStackController.RemoveCommand(m_Name+"/Right/Bypass");
    m_CommandStackController.RemoveCommand(m_Name+"/Right/WetDry");
    m_CommandStackController.RemoveCommand(m_Name+"/Right/Feedback");
    m_CommandStackController.RemoveCommand(m_Name+"/Right/DelayMilliSeconds");
    Close();
}

std::string CStereoDelayModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CStereoDelayModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CStereoDelayModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CStereoDelayModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CStereoDelayModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/Left/Bypass", "Bypass", true);
    ParameterVisitor.FloatParameter(m_Name+"/Left/WetDry", "WetDry", 0.4f, 0.0f, 1.0f, 0.01f, 3);
    ParameterVisitor.FloatParameter(m_Name+"/Left/DelayMilliSeconds", "Delay", 247.0f, 0.0f, 5000.0f, 1.0f, 1);
    ParameterVisitor.FloatParameter(m_Name+"/Left/Feedback", "Feedback", 0.5f, 0.0f, 1.0f, 0.01f, 3);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/Right/Bypass", "Bypass", true);
    ParameterVisitor.FloatParameter(m_Name+"/Right/WetDry", "WetDry", 0.4f, 0.0f, 1.0f, 0.01f, 3);
    ParameterVisitor.FloatParameter(m_Name+"/Right/DelayMilliSeconds", "Delay", 253.0f, 0.0f, 5000.0f, 1.0f, 1);
    ParameterVisitor.FloatParameter(m_Name+"/Right/Feedback", "Feedback", 0.5f, 0.0f, 1.0f, 0.01f, 3);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CStereoDelayModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CStereoDelayFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CStereoDelayModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
