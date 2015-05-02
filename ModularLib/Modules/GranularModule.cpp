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
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SampleGrab").BoolValue(false), [this](const SCmdStackItem& Item) { m_Filter->SetSampleGrab(Item.BoolValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/SampleSize").IntValue(15), [this](const SCmdStackItem& Item) { m_Filter->SetSampleSize(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/GrainSize").IntValue(12), [this](const SCmdStackItem& Item) { m_Filter->SetGrainSize(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/GrainDensity").IntValue(11), [this](const SCmdStackItem& Item) { m_Filter->SetGrainDensity(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/GrainSpeed").IntValue(1<<CGrain<float>::SpeedScale), [this](const SCmdStackItem& Item) { m_Filter->SetGrainSpeed(Item.IntValue()); });
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/PositionSpeed").IntValue(256), [this](const SCmdStackItem& Item) { m_Filter->SetPositionSpeed(Item.IntValue()); });
}

CGranularModule::~CGranularModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/SampleGrab");
    m_CommandStackController.RemoveCommand(m_Name+"/SampleSize");
    m_CommandStackController.RemoveCommand(m_Name+"/GrainSize");
    m_CommandStackController.RemoveCommand(m_Name+"/GrainDensity");
    m_CommandStackController.RemoveCommand(m_Name+"/GrainSpeed");
    m_CommandStackController.RemoveCommand(m_Name+"/PositionSpeed");
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
    ParameterVisitor.IntegerParameter(m_Name+"/SampleSize", "SampleSize", 17, 10, 17, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/GrainSize", "GrainSize", 12, 8, 16, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/GrainDensity", "GrainDensity", 11, 4, 18, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/GrainSpeed", "GrainSpeed", 1<<CGrain<float>::SpeedScale, 1, 8*(1<<CGrain<float>::SpeedScale), 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/PositionSpeed", "PositionSpeed", 256, 1, 256*16, 1);
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
