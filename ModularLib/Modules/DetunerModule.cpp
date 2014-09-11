#include "DetunerModule.h"
#include "DetunerFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CDetunerModule::CDetunerModule(const std::string& Name, int Size, CCommandStackController& CommandStackController)
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
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/Detune", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetDetune(idx, Item.s_FloatValue); });
        m_CommandStackController.AddCommand({m_Name+"/"+std::to_string(idx)+"/OctaveShift", false, 0, 0.0f}, [idx,this](const SCmdStackItem& Item) { m_Filter->SetOctaveShift(idx, Item.s_IntValue); });
    }
}

CDetunerModule::~CDetunerModule()
{
    // remove from command stack
    for(int idx = 0; idx<m_Size; ++idx)
    {
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/Detune");
        m_CommandStackController.RemoveCommand(m_Name+"/"+std::to_string(idx)+"/OctaveShift");
    }
    Close();
}

std::string CDetunerModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CDetunerModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CDetunerModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CDetunerModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CDetunerModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    for(int idx = 0; idx<m_Size; ++idx)
    {
        ParameterVisitor.StartLine();
        ParameterVisitor.FloatParameter(m_Name+"/"+std::to_string(idx)+"/Detune", "Detune"+std::to_string(idx), 0.0f, -1.0f, 1.0f, 0.001, 4);
        ParameterVisitor.IntegerParameter(m_Name+"/"+std::to_string(idx)+"/OctaveShift", "Octave"+std::to_string(idx), 0, -8, 8, 1);
        ParameterVisitor.FinishLine();
    }
    ParameterVisitor.Finish();
}

bool CDetunerModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CDetunerFilter(m_Size));
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CDetunerModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}

