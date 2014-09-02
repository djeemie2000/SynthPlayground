#include "CombinorModule.h"
#include "CombinorFilter.h"
#include "JackIOManager.h"

CCombinorModule::CCombinorModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter(new CCombinorFilter())
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // TODO function add to CommandStackController
}

CCombinorModule::~CCombinorModule()
{
    //CommandStackController
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

void CCombinorModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
    //CommandStackController
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
