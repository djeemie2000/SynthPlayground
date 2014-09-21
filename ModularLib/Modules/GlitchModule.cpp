#include "GlitchModule.h"
#include "GlitchFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CGlitchModule::CGlitchModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand({m_Name+"/OctaveShift", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetOctaveShift(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/GrainSizeOut", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGrainSizeOut(Item.s_IntValue); });
    m_CommandStackController.AddCommand({m_Name+"/GrainSizeIn", false, 0, 0.0f}, [this](const SCmdStackItem& Item) { m_Filter->SetGrainSizeIn(Item.s_IntValue); });
}

CGlitchModule::~CGlitchModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/OctaveShift");
    m_CommandStackController.RemoveCommand(m_Name+"/GrainSizeOut");
    m_CommandStackController.RemoveCommand(m_Name+"/GrainSizeIn");
    Close();
}

std::string CGlitchModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CGlitchModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CGlitchModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CGlitchModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CGlitchModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/OctaveShift", "OctaveShift", 0, -3, 3, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/GrainSizeOut", "GrainSizeOut", 6, 4, 8, 1);
    ParameterVisitor.IntegerParameter(m_Name+"/GrainSizeIn", "GrainSizeIn", 6, 3, 8, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CGlitchModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CGlitchFilter());
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CGlitchModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

