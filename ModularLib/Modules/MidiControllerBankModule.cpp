#include "MidiControllerBankModule.h"
#include "MidiControllerBankFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CMidiControllerBankModule::CMidiControllerBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Size(Size)
 , m_Filter(new CMidiControllerBankFilter(Size))
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/"+std::to_string(idx)+"/Parameter").IntValue(-1), [idx,this](const SCmdStackItem& Item) { m_Filter->SetParam(idx, Item.s_IntValue); });
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/"+std::to_string(idx)+"/Min").FloatValue(0.0f), [idx,this](const SCmdStackItem& Item) { m_Filter->SetMin(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/"+std::to_string(idx)+"/Max").FloatValue(1.0f), [idx,this](const SCmdStackItem& Item) { m_Filter->SetMax(idx, Item.s_FloatValue); });
    }
}

CMidiControllerBankModule::~CMidiControllerBankModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Parameter");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Min");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Max");
    }
    Close();
}

std::string CMidiControllerBankModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMidiControllerBankModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMidiControllerBankModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMidiControllerBankModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMidiControllerBankModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.IntegerParameter(m_Name+"/"+std::to_string(idx)+"/Parameter", "Param"+std::to_string(idx), -1, -1, 127, 1);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Min", "Min"+std::to_string(idx), 0.0f, -1000000.0f, 100000.0f, 0.01, 3);
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Max", "Max"+std::to_string(idx), 1.0f, -1000000.0f, 100000.0f, 0.01, 3);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CMidiControllerBankModule::Open()
{
    return m_IOManager->OpenClient(m_Name)
            && m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
}

bool CMidiControllerBankModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
