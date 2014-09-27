#include "ControllerBankModule.h"
#include "ControllerBankFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CControllerBankModule::CControllerBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Size(Size)
 , m_Filter(new CControllerBankFilter(Size))
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Value", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->Set(idx, Item.s_FloatValue); });
    }
}

CControllerBankModule::~CControllerBankModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Value");
    }
    Close();
}

std::string CControllerBankModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CControllerBankModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CControllerBankModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CControllerBankModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CControllerBankModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Value", "Value"+std::to_string(idx), 0.0f, -100000.0f, 100000.0f, 0.001, 4);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CControllerBankModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CControllerBankModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
