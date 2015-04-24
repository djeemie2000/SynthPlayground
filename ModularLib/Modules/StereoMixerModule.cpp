#include "StereoMixerModule.h"
#include "StereoMixerFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CStereoMixerModule::CStereoMixerModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Size(Size)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Volume", false, 0, 0.25f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetVolume(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Pan", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetPan(idx, Item.s_FloatValue); });
    }
    m_CommandStackController.AddCommand({m_Name+"/MasterVolume", false, 0, 0.5f}, [this](const SCmdStackItem& Item) { m_Filter->SetMasterVolume(Item.s_FloatValue); });
}

CStereoMixerModule::~CStereoMixerModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Volume");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Pan");
    }
    m_CommandStackController.RemoveCommand(m_Name+"/MasterVolume");
    Close();
}

std::string CStereoMixerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CStereoMixerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CStereoMixerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CStereoMixerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CStereoMixerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/MasterVolume", "MasterVolume", 0.5f, 0.0000f, 2.0f, 0.01, 3);
    ParameterVisitor.FinishLine();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Volume", "Volume"+std::to_string(idx), 0.25f, 0.0000f, 2.0f, 0.01, 3);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Pan", "Pan"+std::to_string(idx), 0.0f, -1.0f, 1.0f, 0.01, 3);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CStereoMixerModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CStereoMixerFilter(m_Size));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CStereoMixerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
