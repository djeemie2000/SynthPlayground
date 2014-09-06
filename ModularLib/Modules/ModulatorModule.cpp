#include "ModulatorModule.h"
#include "ModulatorFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CModulatorModule::CModulatorModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
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
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/ModAmt", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetModAmt(idx, Item.s_FloatValue); });
    }
    m_CommandStackController.AddCommand({m_Name+"/Offset", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetOffset(Item.s_FloatValue); });
    m_CommandStackController.AddCommand({m_Name+"/LimitMode", false, 1, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetLimitMode(Item.s_IntValue); });
}

CModulatorModule::~CModulatorModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/ModAmt");
    }
    m_CommandStackController.RemoveCommand(m_Name+"/Offset");
    m_CommandStackController.RemoveCommand(m_Name+"/LimitModes");
    Close();
}

std::string CModulatorModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CModulatorModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CModulatorModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CModulatorModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CModulatorModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.FloatParameter(m_Name+"/Offset", "Offset", 0.0f, -1.0f, 1.0f, 0.01, 3);
    ParameterVisitor.SelectionParameter(m_Name+"/LimitMode", "LimitMode", 1, {"None", "Bipolar", "Unipolar"});
    ParameterVisitor.FinishLine();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/ModAmt", "ModAmt"+std::to_string(idx), 0.0f, -1.0f, 1.0f, 0.01, 3);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CModulatorModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CModulatorFilter(m_Size));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CModulatorModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
