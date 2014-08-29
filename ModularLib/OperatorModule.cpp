#include "OperatorModule.h"
#include "OperatorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

COperatorModule::COperatorModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new COperatorFilter())
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Select", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->Select(Item.s_IntValue); });
    // Open here?
    Open();
}

COperatorModule::~COperatorModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Select");
    Close();
}

std::string COperatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names COperatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names COperatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names COperatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void COperatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.SelectionParameter(m_Name+"/Select", "WaveForm", 0, CSelectableOperatorFactory::SelectionList());
    ParameterVisitor.Finish();
}

bool COperatorModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool COperatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
