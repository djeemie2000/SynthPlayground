#include "WaveFolderModule.h"
#include "WaveFolderFilter.h"
#include "JackIOManager.h"

CWaveFolderModule::CWaveFolderModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CWaveFolderFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CWaveFolderModule::~CWaveFolderModule()
{
    Close();
}

std::string CWaveFolderModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CWaveFolderModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CWaveFolderModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CWaveFolderModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CWaveFolderModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CWaveFolderModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CWaveFolderModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
