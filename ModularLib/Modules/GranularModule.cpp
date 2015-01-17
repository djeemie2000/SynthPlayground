#include "GranularModule.h"
#include "GranularFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"

CGranularModule::CGranularModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/SampleGrab", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetSampleGrab(Item.BoolValue()); });
    m_CommandStackController.AddCommand({m_Name+"/SampleSize", false, 1<<15, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetSampleSize(Item.IntValue()); });
}

CGranularModule::~CGranularModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/SampleGrab");
    m_CommandStackController.RemoveCommand(m_Name+"/SampleSize");
    Close();
}

std::string CGranularModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CGranularModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CGranularModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CGranularModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CGranularModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.BooleanParameter(m_Name+"/SampleGrab", "SampleGrab", false);
    ParameterVisitor.IntegerParameter(m_Name+"/SampleSize", "SampleSize", m_Filter->GetSampleCapacity(), 1<<10, m_Filter->GetSampleCapacity(), 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CGranularModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CGranularFilter());
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CGranularModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
