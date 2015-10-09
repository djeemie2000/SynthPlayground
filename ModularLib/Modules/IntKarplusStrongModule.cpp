#include "IntKarplusStrongModule.h"
#include "IntKarplusStrongFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CIntKarplusStrongModule::CIntKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/Poles").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetPoles(Item.IntValue()); });
}

CIntKarplusStrongModule::~CIntKarplusStrongModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
    Close();
}

std::string CIntKarplusStrongModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CIntKarplusStrongModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CIntKarplusStrongModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CIntKarplusStrongModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CIntKarplusStrongModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/Poles", "Poles", 12, 1, 12, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CIntKarplusStrongModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CIntKarplusStrongFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CIntKarplusStrongModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
