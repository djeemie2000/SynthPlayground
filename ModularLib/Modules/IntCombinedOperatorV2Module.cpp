#include "IntCombinedOperatorV2Module.h"
#include "IntCombinedOperatorV2Filter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "IntCombinedOperatorV2.h"
#include "ModuleParameterVisitorI.h"

CIntCombinedOperatorV2Module::CIntCombinedOperatorV2Module(const std::string& Name, CCommandStackController &CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Name(Name)
    , m_Filter()
    , m_IOManager(new CJackIOManager())
{
    // Open here
    Open();
    // function add to CommandStackController
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectCombinor").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectCombinor1(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorA").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorA(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorB").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorB(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/FrequencyMultiplierA").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SetFrequencyMultiplierA(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/FrequencyMultiplierB").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SetFrequencyMultiplierB(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/OperatorACarrier").BoolValue(true), [this](const SCmdStackItem& Item) { m_Filter->SetOperatorACarrier(Item.BoolValue()); });
}

CIntCombinedOperatorV2Module::~CIntCombinedOperatorV2Module()
{
    m_CommandStackController.RemoveCommand(m_Name+"/OperatorACarrier");
    m_CommandStackController.RemoveCommand(m_Name+"/FrequencyMultiplierB");
    m_CommandStackController.RemoveCommand(m_Name+"/FrequencyMultiplierA");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorB");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorA");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectCombinor");

    Close();
}

std::string CIntCombinedOperatorV2Module::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntCombinedOperatorV2Module::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntCombinedOperatorV2Module::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntCombinedOperatorV2Module::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntCombinedOperatorV2Module::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorA", "OperatorA", 0, isl::CIntCombinedOperatorV2<1,2,3>::GetOperatorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectCombinor", "Combinor", 0, isl::CIntCombinedOperatorV2<1,2,3>::GetCombinorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorB", "OperatorB", 0, isl::CIntCombinedOperatorV2<1,2,3>::GetOperatorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/FrequencyMultiplierA", "DetuneA", 1024, 64, 4096, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/FrequencyMultiplierB", "DetuneB", 1024, 64, 4096, 1);
    ParameterVisitor.BooleanParameter(m_Name+"/OperatorACarrier", "OperatorACarrier", true);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CIntCombinedOperatorV2Module::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntCombinedOperatorV2Filter( m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CIntCombinedOperatorV2Module::Close()
{
    m_IOManager->CloseClient();
    return true;
}
