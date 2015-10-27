#include "IntCombFilterModule.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"
#include "CommandStackController.h"
#include "IntCombFilterFilter.h"

CIntCombFilterModule::CIntCombFilterModule(const std::string& Name, CCommandStackController &CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
}

CIntCombFilterModule::~CIntCombFilterModule()
{
    // remove from command stack
    Close();
}

std::string CIntCombFilterModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntCombFilterModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntCombFilterModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntCombFilterModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntCombFilterModule::Accept(IModuleParameterVisitor &/*ParameterVisitor*/) const
{
}

bool CIntCombFilterModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntCombFilterFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CIntCombFilterModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
