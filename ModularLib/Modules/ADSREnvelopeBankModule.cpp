#include "ADSREnvelopeBankModule.h"
#include "ADSREnvelopeBankFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CADSREnvelopeBankModule::CADSREnvelopeBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
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
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Attack", false, 0, 10.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetAttackMilliSeconds(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Decay", false, 0, 10.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetDecayMilliSeconds(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Sustain", false, 0, 1.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetSustain(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Release", false, 0, 10.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetReleaseMilliSeconds(idx, Item.s_FloatValue); });
    }
}

CADSREnvelopeBankModule::~CADSREnvelopeBankModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Attack");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Decay");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Sustain");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Release");
    }
    Close();
}

std::string CADSREnvelopeBankModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CADSREnvelopeBankModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CADSREnvelopeBankModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CADSREnvelopeBankModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CADSREnvelopeBankModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Attack", "Attack"+std::to_string(idx), 10.0f, 0.0f, 10000.0f, 1.0f, 1);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Decay", "Decay"+std::to_string(idx), 10.0f, 0.0f, 10000.0f, 1.0f, 1);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Sustain", "Sustain"+std::to_string(idx), 1.0f, 0.0f, 10.0f, 0.01, 3);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Release", "Release"+std::to_string(idx), 10.0f, 0.0f, 10000.0f, 0.01, 1);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CADSREnvelopeBankModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CADSREnvelopeBankFilter(m_Size, m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CADSREnvelopeBankModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
