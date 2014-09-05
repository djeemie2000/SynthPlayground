#include "CombinorModule.h"
#include "CombinorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "SelectableCombinorFactory.h"
#include "ModuleParameterVisitorI.h"

CCombinorModule::CCombinorModule(const std::string& Name, CCommandStackController &CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Name(Name)
    , m_Filter(new CCombinorFilter())
    , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // TODO function add to CommandStackController
    m_CommandStackController.AddCommand({m_Name+"/Select", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->Select(Item.s_IntValue); });
}

CCombinorModule::~CCombinorModule()
{
    m_CommandStackController.RemoveCommand(m_Name+"/Select");
    Close();
}

std::string CCombinorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CCombinorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CCombinorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CCombinorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CCombinorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.SelectionParameter(m_Name+"/Select", "Combinor", 0, CSelectableCombinorFactory::SelectionList());
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CCombinorModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CCombinorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
