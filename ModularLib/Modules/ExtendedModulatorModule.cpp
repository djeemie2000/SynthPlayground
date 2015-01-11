#include "ExtendedModulatorModule.h"
#include "ExtendedModulatorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CExtendedModulatorModule::CExtendedModulatorModule(const std::string& Name, int Size)
 : m_Name(Name)
 , m_Size(Size)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
}

CExtendedModulatorModule::~CExtendedModulatorModule()
{
    Close();
}

std::string CExtendedModulatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CExtendedModulatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CExtendedModulatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CExtendedModulatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CExtendedModulatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.Finish();
}

bool CExtendedModulatorModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CExtendedModulatorFilter(m_Size));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CExtendedModulatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
