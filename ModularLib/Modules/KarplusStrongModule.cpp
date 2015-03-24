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
    m_CommandStackController.AddCommand({m_Name+"/Poles", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetPoles(Item.IntValue()); });
    // Open here?
    Open();
}

CKarplusStrongModule::~CKarplusStrongModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
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
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/Poles", "Poles", 1, 1, 24, 1);
    ParameterVisitor.FinishLine();
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
