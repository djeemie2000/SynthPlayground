#include "Distortion1Module.h"
#include "Distortion1Filter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CDistortion1Module::CDistortion1Module(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CDistortion1Filter())
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/Drive", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetDrive(Item.s_FloatValue); });
    // Open here?
    Open();
}

CDistortion1Module::~CDistortion1Module()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Drive");
    Close();
}

std::string CDistortion1Module::GetName() const
{
    return m_Name;
}

IModularModule::Names CDistortion1Module::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CDistortion1Module::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CDistortion1Module::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CDistortion1Module::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/Drive", "Drive", 0.0f, 0.0f, 1.0f, 0.01, 3);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CDistortion1Module::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CDistortion1Module::Close()
{
    m_IOManager->CloseClient();
    return true;
}
