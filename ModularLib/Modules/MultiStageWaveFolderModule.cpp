#include "MultiStageWaveFolderModule.h"
#include "MultiStageWaveFolderFilter.h"
#include "JackIOManager.h"
#include "CommandStackController.h"
#include "ModuleParameterVisitorI.h"
#include "SelectableOperatorFactory.h"

CMultiStageWaveFolderModule::CMultiStageWaveFolderModule(const std::string& Name, CCommandStackController& CommandStackController)
 : m_CommandStackController(CommandStackController)
 , m_Name(Name)
 , m_Filter()
 , m_IOManager(new CJackIOManager())
{
    // Open here?
    Open();
    // command stack stuff for filter
    m_CommandStackController.AddCommand(SCmdStackItem(m_Name+"/NumStages").IntValue(1), [this](const SCmdStackItem& Item) { m_Filter->SetNumStages(Item.s_IntValue); });
}

CMultiStageWaveFolderModule::~CMultiStageWaveFolderModule()
{
    // remove from command stack
    m_CommandStackController.RemoveCommand(m_Name+"/NumStages");
    Close();
}

std::string CMultiStageWaveFolderModule::GetName() const
{
    return m_Name;
}

IModularModule::Names CMultiStageWaveFolderModule::GetInputNames() const
{
    return m_Filter->GetInputNames();
}

IModularModule::Names CMultiStageWaveFolderModule::GetOutputNames() const
{
    return m_Filter->GetOutputNames();
}

IModularModule::Names CMultiStageWaveFolderModule::GetMidiInputNames() const
{
    return m_Filter->GetMidiInputNames();
}

void CMultiStageWaveFolderModule::Accept(IModuleParameterVisitor &ParameterVisitor) const
{
    ParameterVisitor.Start();
    ParameterVisitor.StartLine();
    ParameterVisitor.IntegerParameter(m_Name+"/NumStages", "NumStages", 1, 1, 8, 1);
    ParameterVisitor.FinishLine();
    ParameterVisitor.Finish();
}

bool CMultiStageWaveFolderModule::Open()
{
    if(m_IOManager->OpenClient(m_Name))
    {
        m_Filter.reset(new CMultiStageWaveFolderFilter());
        return m_IOManager->OpenAudioFilter(m_Filter)
            && m_IOManager->ActivateClient();
    }
    return false;
}

bool CMultiStageWaveFolderModule::Close()
{
    m_IOManager->CloseClient();
    return true;
}
