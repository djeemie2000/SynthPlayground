#include "PhasorModule.h"
#include "PhasorFilter.h"
#include "JackIOManager.h"
#include "ModuleParameterVisitorI.h"

CPhasorModule::CPhasorModule(const std::string& Name)
 : m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CPhasorModule::~CPhasorModule()
{
    Close();
}

std::string CPhasorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPhasorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPhasorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPhasorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPhasorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CPhasorModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CPhasorFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CPhasorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
