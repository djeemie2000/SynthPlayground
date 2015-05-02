#include "EnvelopeFollowerModule.h"
#include "EnvelopeFollowerFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CEnvelopeFollowerModule::CEnvelopeFollowerModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/AttackMilliSeconds").FloatValue(1.0f), [this](const SCmdStackItem& Item) { m_Filter->SetAttack(Item.s_FloatValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/ReleaseMilliSeconds").FloatValue(1.0f), [this](const SCmdStackItem& Item) { m_Filter->SetRelease(Item.s_FloatValue); });
}

CEnvelopeFollowerModule::~CEnvelopeFollowerModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/AttackMilliSeconds");
    m_CommandStackController.RemoveCommand(m_Name+"/ReleaseMilliSeconds");
    Close();
}

std::string CEnvelopeFollowerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CEnvelopeFollowerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CEnvelopeFollowerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CEnvelopeFollowerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CEnvelopeFollowerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/AttackMilliSeconds", "Attack", 1.0f, 0.0f, 10000.0f, 1.00, 2);
    ParameterVisitor.FloatParameter(m_Name+"/ReleaseMilliSeconds", "Release", 1.0f, 0.0f, 10000.0f, 1.00, 2);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CEnvelopeFollowerModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CEnvelopeFollowerFilter(m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CEnvelopeFollowerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
