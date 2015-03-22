#include "KarplusStrongModule.h"
#include "KarplusStrongModule.h"
#include "KarplusStrongFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CKarplusStrongModule::CKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // command stack stuff for filter
    // Open here?
    Open();
}

CKarplusStrongModule::~CKarplusStrongModule()
{
    // remove from command stack
    Close();
}

std::string CKarplusStrongModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CKarplusStrongModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CKarplusStrongModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CKarplusStrongModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CKarplusStrongModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CKarplusStrongModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CKarplusStrongFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CKarplusStrongModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
