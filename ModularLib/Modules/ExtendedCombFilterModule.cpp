#include "ExtendedCombFilterModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "ExtendedCombFilterFilter.h"

CExtendedCombFilterModule::CExtendedCombFilterModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
}

CExtendedCombFilterModule::~CExtendedCombFilterModule()
{
    // remove from command stack
    Close();
}

std::string CExtendedCombFilterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CExtendedCombFilterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CExtendedCombFilterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CExtendedCombFilterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CExtendedCombFilterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CExtendedCombFilterModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CExtendedCombFilterFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CExtendedCombFilterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
