#include "ConstModule.h"
#include "ConstFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CConstModule::CConstModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CConstFilter())
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Value", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->Set(Item.s_FloatValue); });
    // Open here?
    Open();
}

CConstModule::~CConstModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Value");
    Close();
}

std::string CConstModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CConstModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CConstModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CConstModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CConstModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.FloatParameter(m_Name+"/Value", "Value", 0.0f, -100000.0f, 100000.0f, 0.001, 4);
    ParameterVisitor.Finish();
}

bool CConstModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CConstModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

