#include "AmpModule.h"
#include "AmpFilter.h"
#include "JackIOManager.h"

CAmpModule::CAmpModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CAmpFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CAmpModule::~CAmpModule()
{
    Close();
}

std::string CAmpModule::GetName() const
{
    return m_Name;
}

bool CAmpModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CAmpModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}