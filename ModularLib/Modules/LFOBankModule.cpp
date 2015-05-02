#include "LFOBankModule.h"
#include "LFOBankFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CLFOBankModule::CLFOBankModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Size(Size)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/"+std::to_string(idx)+"/Select").IntValue(0), [idx,this](const SCmdStackItem& Item) { m_Filter->Select(idx, Item.s_IntValue); });
        m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/"+std::to_string(idx)+"/Frequency").FloatValue(1.0f), [idx,this](const SCmdStackItem& Item) { m_Filter->SetFrequency(idx, Item.s_FloatValue); });
    }
}

CLFOBankModule::~CLFOBankModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Select");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Frequency");
    }
    Close();
}

std::string CLFOBankModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CLFOBankModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CLFOBankModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CLFOBankModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CLFOBankModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Frequency", "Frequency"+std::to_string(idx), 1.0f, 0.01f, 100000.0f, 0.01f, 4);
        ParameterVisitor.SelectionParameter(m_Name+"/"+std::to_string(idx)+"/Select", "Waveform"+std::to_string(idx), 0, CSelectableOperatorFactory::SelectionList());
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CLFOBankModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CLFOBankFilter(m_Size, m_IOManager->SamplingFrequency()));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CLFOBankModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

