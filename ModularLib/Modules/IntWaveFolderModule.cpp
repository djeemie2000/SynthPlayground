#include "IntWaveFolderModule.h"
#include "IntWaveFolderFilter.h"
#include "JackIOManager.h"

CIntWaveFolderModule::CIntWaveFolderModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CIntWaveFolderFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CIntWaveFolderModule::~CIntWaveFolderModule()
{
    Close();
}

std::string CIntWaveFolderModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntWaveFolderModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntWaveFolderModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntWaveFolderModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntWaveFolderModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CIntWaveFolderModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CIntWaveFolderModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
