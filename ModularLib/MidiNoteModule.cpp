#include "MidiNoteModule.h"
#include "MidiNoteFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"

CMidiNoteModule::CMidiNoteModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CMidiNoteFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CMidiNoteModule::~CMidiNoteModule()
{
    Close();
}

std::string CMidiNoteModule::GetName() const
{
    return m_Name;
}

bool CMidiNoteModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CMidiNoteModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
