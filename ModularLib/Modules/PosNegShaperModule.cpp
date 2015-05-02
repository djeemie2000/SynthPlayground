#include "PosNegShaperModule.h"
#include "PosNegShaperFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CPosNegShaperModule::CPosNegShaperModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CPosNegShaperFilter())
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Invert").BoolValue(false), [this](const SCmdStackItem& Item) { m_Filter->SetInvert(Item.s_BoolValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/InverterMode").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetInverterMode(Item.s_IntValue); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/DerectifierMode").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetDerectifierMode(Item.s_IntValue); });
    // Open here?
    Open();
}

CPosNegShaperModule::~CPosNegShaperModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Invert");
    m_CommandStackController.RemoveCommand(m_Name+"/InverterMode");
    m_CommandStackController.RemoveCommand(m_Name+"/DerectifierMode");
    Close();
}

std::string CPosNegShaperModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPosNegShaperModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPosNegShaperModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPosNegShaperModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPosNegShaperModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/Invert", "Invert", false);
    ParameterVisitor.IntegerParameter(m_Name+"/InverterMode", "Inverter Mode", 1, 1, 4, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/DerectifierMode", "Derectifier Mode", 1, 1, 4, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CPosNegShaperModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CPosNegShaperModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
