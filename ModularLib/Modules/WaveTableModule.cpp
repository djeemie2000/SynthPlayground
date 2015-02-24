#include "WaveTableModule.h"
#include "WaveTableFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CWaveTableModule::CWaveTableModule(const std::string& Name, CCommandStackController &CommandStackController)
    : m_CommandStackController(CommandStackController)
    , m_Name(Name)
    , m_Filter(new CWaveTableFilter())
    , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CWaveTableModule::~CWaveTableModule()
{
    Close();
}

std::string CWaveTableModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CWaveTableModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CWaveTableModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CWaveTableModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CWaveTableModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CWaveTableModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CWaveTableModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
