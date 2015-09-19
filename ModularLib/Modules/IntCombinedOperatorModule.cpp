#include "IntCombinedOperatorModule.h"
#include "IntCombinedOperatorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "IntCombinedOperator.h"
#include "ModuleParameterVisitorI.h"

CIntCombinedOperatorModule::CIntCombinedOperatorModule(const std::string& Name, CCommandStackController &CommandStackController)
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
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectCombinor2").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectCombinor2(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorC").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorC(Item.IntValue()); });
}

CIntCombinedOperatorModule::~CIntCombinedOperatorModule()
{
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorC");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectCombinor2");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorB");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorA");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectCombinor");
    Close();
}

std::string CIntCombinedOperatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntCombinedOperatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntCombinedOperatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntCombinedOperatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntCombinedOperatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorA", "OperatorA", 0, isl::CIntCombinedOperator<12>::GetOperatorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectCombinor", "Combinor", 0, isl::CIntCombinedOperator<12>::GetCombinorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorB", "OperatorB", 0, isl::CIntCombinedOperator<12>::GetOperatorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorC", "OperatorC", 0, isl::CIntCombinedOperator<12>::GetOperatorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectCombinor2", "Combinor2", 0, isl::CIntCombinedOperator<12>::GetCombinorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CIntCombinedOperatorModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntCombinedOperatorFilter( m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CIntCombinedOperatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
