#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StepSequencerController.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"
#include "JackMidiSource.h"

namespace
{
    CmdFunctionMap BuildFunctionMap(CStepSequencerController& Controller)
    {
        CmdFunctionMap FunctionMap;

        // StepSequencer
        FunctionMap["StepSequencer/BeatsPerMinute"] = [&Controller](const SCmdStackItem& Item){ Controller.SetBeatsPerMinute(Item.s_FloatValue); };
        FunctionMap["StepSequencer/BarsPerBeat"] = [&Controller](const SCmdStackItem& Item){ Controller.SetBarsPerBeat(Item.s_IntValue); };
        FunctionMap["StepSequencer/Go"] = [&Controller](const SCmdStackItem& Item){ if(Item.s_BoolValue) { Controller.Start(); } else {Controller.Stop(); } };
        FunctionMap["StepSequencer/NumSteps"] = [&Controller](const SCmdStackItem& Item){ Controller.SetNumSteps(Item.s_IntValue); };
        for(int Step = 0; Step<Controller.GetMaxNumSteps(); ++Step)
        {
            FunctionMap["StepSequencer/Active/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetActive(Step, Item.s_BoolValue); };
            FunctionMap["StepSequencer/Note/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetNote(Step, static_cast<ENote>(Item.s_IntValue)); };
            FunctionMap["StepSequencer/Octave/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetOctave(Step, static_cast<EOctave>(Item.s_IntValue)); };
        }

        return FunctionMap;
    }

    CmdStack BuildDefaultCommandStack()
    {
        CmdStack Stack;

        // StepSequencer
        Stack.push_back({"StepSequencer/BeatsPerMinute", false, 0, 120.0f});
        Stack.push_back({"StepSequencer/BarsPerBeat", false, 2, 0.0f});
        Stack.push_back({"StepSequencer/Go", false, 0, 0.0f});
        Stack.push_back({"StepSequencer/NumSteps", false, 8, 0.0f});
        for(int Step = 0; Step<8; ++Step)
        {
            Stack.push_back({"StepSequencer/Active/"+std::to_string(Step), false, 0, 0.0f});
            Stack.push_back({"StepSequencer/Note/"+std::to_string(Step), false, static_cast<int>(ENote::A), 0.0f });
            Stack.push_back({"StepSequencer/Octave/"+std::to_string(Step), false, 2, 0.0f});
        }

        return Stack;
    }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_AudioOutput()
  , m_Controller()
{
    ui->setupUi(this);

    m_AudioOutput.reset(new CJackIOManager());
    m_AudioOutput->OpenClient("StepSequencer");

    std::shared_ptr<CJackMidiSource> MidiSource(new CJackMidiSource());
    m_Controller.reset(new CStepSequencerController(m_AudioOutput->SamplingFrequency(), MidiSource, MidiSource));
    m_CommandStackController.reset(new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack()));

    // build gui
    guiutils::AddStepSequencer(ui->groupBox_StepSequencer, this, m_Controller->GetMaxNumSteps(), "StepSequencer", *m_CommandStackController);

    ui->groupBox_StepSequencer->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenMidiOutput("MidiOut", m_Controller);
    m_AudioOutput->ActivateClient();
}

MainWindow::~MainWindow()
{
    m_AudioOutput->CloseClient();

    delete ui;
}
