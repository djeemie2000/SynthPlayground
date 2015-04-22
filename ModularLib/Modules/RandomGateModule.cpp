#include "RandomGateModule.h"
#include "RandomGateFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CRandomGateModule::CRandomGateModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CRandomGateFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/GateOpenScale", false, 14, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateOpenScale(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/GateOpenCenter", false, 0, 0.5f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateOpenCenter(Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/GateOpenVariation", false, 0, 1.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateOpenVariation(Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/GateCloseScale", false, 14, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateCloseScale(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/GateCloseCenter", false, 0, 0.5f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateCloseCenter(Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/GateCloseVariation", false, 0, 1.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGateCloseVariation(Item.s_FloatValue); });
}

CRandomGateModule::~CRandomGateModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/GateOpenScale");
    m_CommandStackController.RemoveCommand(m_Name+"/GateOpenCenter");
    m_CommandStackController.RemoveCommand(m_Name+"/GateOpenVariation");
    m_CommandStackController.RemoveCommand(m_Name+"/GateCloseScale");
    m_CommandStackController.RemoveCommand(m_Name+"/GateCloseCenter");
    m_CommandStackController.RemoveCommand(m_Name+"/GateCloseVariation");
    Close();
}

std::string CRandomGateModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CRandomGateModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CRandomGateModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CRandomGateModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CRandomGateModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/GateOpenCenter", "Center", 0.5f, 0.0f, 1.0f, 0.01, 3);
    ParameterVisitor.FloatParameter(m_Name+"/GateOpenVariation", "Variation", 0.0f, 0.0f, 1.0f, 0.01, 3);
    ParameterVisitor.IntegerParameter(m_Name+"/GateOpenScale", "Offset", 14, 1, 20, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/GateCloseCenter", "Center", 0.5f, 0.0f, 1.0f, 0.01, 3);
    ParameterVisitor.FloatParameter(m_Name+"/GateCloseVariation", "Variation", 0.0f, 0.0f, 1.0f, 0.01, 3);
    ParameterVisitor.IntegerParameter(m_Name+"/GateCloseScale", "Offset", 14, 1, 20, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CRandomGateModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CRandomGateModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
