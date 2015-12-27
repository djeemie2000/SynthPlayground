#include "Lpf4PoleModule.h"
#include "Lpf4PoleFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CLpf4PoleModule::CLpf4PoleModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter(new CLpf4PoleFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CLpf4PoleModule::~CLpf4PoleModule()
{
    Close();
}

std::string CLpf4PoleModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CLpf4PoleModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CLpf4PoleModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CLpf4PoleModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CLpf4PoleModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CLpf4PoleModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CLpf4PoleModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
