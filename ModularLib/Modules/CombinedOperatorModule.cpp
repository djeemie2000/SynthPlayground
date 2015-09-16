#include "CombinedOperatorModule.h"
#include "CombinedOperatorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "CombinedOperator.h"
#include "ModuleParameterVisitorI.h"

CCombinedOperatorModule::CCombinedOperatorModule(const std::string& Name, CCommandStackController &CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Name(Name)
    , m_Filter()
    , m_IOManager(new CJackIOManager())
{
    // Open here
    Open();
    // function add to CommandStackController
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectCombinor").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectCombinor(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorA").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorA(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorB").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorB(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectCombinor2").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectCombinor2(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SelectOperatorC").IntValue(0), [this](const SCmdStackItem& Item) { m_Filter->SelectOperatorC(Item.IntValue()); });
}

CCombinedOperatorModule::~CCombinedOperatorModule()
{
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorC");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectCombinor2");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorB");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectOperatorA");
    m_CommandStackController.RemoveCommand(m_Name+"/SelectCombinor");
    Close();
}

std::string CCombinedOperatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CCombinedOperatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CCombinedOperatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CCombinedOperatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CCombinedOperatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorA", "OperatorA", 0, CCombinedOperator<float>::GetOperatorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectCombinor", "Combinor", 0, CCombinedOperator<float>::GetCombinorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorB", "OperatorB", 0, CCombinedOperator<float>::GetOperatorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/SelectOperatorC", "OperatorC", 0, CCombinedOperator<float>::GetOperatorNames());
    ParameterVisitor.SelectionParameter(m_Name+"/SelectCombinor2", "Combinor2", 0, CCombinedOperator<float>::GetCombinorNames());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CCombinedOperatorModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CCombinedOperatorFilter( m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CCombinedOperatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
