#include "PolyKarplusStrongModule.h"
#include "PolyKarplusStrongFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CPolyKarplusStrongModule::CPolyKarplusStrongModule(const std::string& Name, CCommandStackController& CommandStackController)
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

CPolyKarplusStrongModule::~CPolyKarplusStrongModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/Poles");
    Close();
}

std::string CPolyKarplusStrongModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CPolyKarplusStrongModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CPolyKarplusStrongModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CPolyKarplusStrongModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CPolyKarplusStrongModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/Poles", "Poles", 8, 1, 8, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CPolyKarplusStrongModule::Open()
{
    bool Ok = false;
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CPolyKarplusStrongFilter(m_IOManager->SamplingFrequency()));
        Ok = m_IOManager->OpenAudioFilter(m_Filter) && m_IOManager->ActivateClient();
    }
    return Ok;
}

bool CPolyKarplusStrongModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
