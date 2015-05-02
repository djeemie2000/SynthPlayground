#include "AsymmetricAmpModule.h"
#include "AsymmetricAmpModule.h"
#include "AsymmetricAmpFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CAsymmetricAmpModule::CAsymmetricAmpModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CAsymmetricAmpFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/AmpPos").FloatValue(1.0f), [this](const SCmdStackItem& Item) { m_Filter->SetAmpPos(Item.s_FloatValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/AmpNeg").FloatValue(1.0f), [this](const SCmdStackItem& Item) { m_Filter->SetAmpNeg(Item.s_FloatValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/AmpOffset").FloatValue(0.0f), [this](const SCmdStackItem& Item) { m_Filter->SetAmpOffset(Item.s_FloatValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/OffsetLockMode").BoolValue(false), [this](const SCmdStackItem& Item) { m_Filter->SetOffsetLockMode(Item.s_BoolValue); });
}

CAsymmetricAmpModule::~CAsymmetricAmpModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/AmpPos");
    m_CommandStackController.RemoveCommand(m_Name+"/AmpNeg");
    m_CommandStackController.RemoveCommand(m_Name+"/AmpOffset");
    m_CommandStackController.RemoveCommand(m_Name+"/OffsetLockMode");
    Close();
}

std::string CAsymmetricAmpModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CAsymmetricAmpModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CAsymmetricAmpModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CAsymmetricAmpModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CAsymmetricAmpModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/AmpPos", "Amp+", 1.0f, -2.0f, 2.0f, 0.01, 3);
    ParameterVisitor.FloatParameter(m_Name+"/AmpNeg", "Amp-", 1.0f, -2.0f, 2.0f, 0.01, 3);
    ParameterVisitor.FloatParameter(m_Name+"/AmpOffset", "Offset", 0.0f, -1.0f, 1.0f, 0.01, 3);
    ParameterVisitor.BooleanParameter(m_Name+"/OffsetLockMode", "OffsetLock", false);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CAsymmetricAmpModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CAsymmetricAmpModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
