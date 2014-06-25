#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QTimer>
#include <QDebug>
#include "QAudioIoDevice.h"
#include "QView.h"
#include "QKeyboardWidget.h"
#include "QScopeWidget.h"
#include "QAudioDeviceWidget.h"
#include "Synth8Controller.h"
#include "GuiItems.h"
#include "MidiInput.h"
#include "NoteQueueMidiInputHandler.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"

namespace
{
    const int SamplingFrequency = 44100;

    CmdFunctionMap BuildFunctionMap(CSynth8Controller& Controller)
    {
        CmdFunctionMap FunctionMap;

        // oscillator (combined folded operator stage)
        FunctionMap["Oscillator/Combinor"] = [&Controller](const SCmdStackItem& Item){  Controller.OnCombinor(Item.s_IntValue); };
        FunctionMap["Oscillator/Sync"] = [&Controller](const SCmdStackItem& ){  Controller.OnSync(); };
        FunctionMap["Oscillator/Amplitude/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnAmplitude(0, Item.s_FloatValue); };
        FunctionMap["Oscillator/Amplitude/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnAmplitude(1, Item.s_FloatValue); };
        FunctionMap["Oscillator/Fold/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFold(0, Item.s_FloatValue); };
        FunctionMap["Oscillator/Fold/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFold(1, Item.s_FloatValue); };
        FunctionMap["Oscillator/FoldModAmt/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFoldModAmount(0, Item.s_FloatValue); };
        FunctionMap["Oscillator/FoldModAmt/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFoldModAmount(1, Item.s_FloatValue); };
        FunctionMap["Oscillator/Operator/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnOperator(0, Item.s_IntValue); };
        FunctionMap["Oscillator/Operator/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnOperator(1, Item.s_IntValue); };
        FunctionMap["Oscillator/FrequencyMultiplier/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFrequencyMultiplier(0, Item.s_FloatValue); };
        FunctionMap["Oscillator/FrequencyMultiplier/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnFrequencyMultiplier(1, Item.s_FloatValue); };
        FunctionMap["Oscillator/PhaseShift/0"] = [&Controller](const SCmdStackItem& Item){  Controller.OnPhaseshift(0, Item.s_FloatValue); };
        FunctionMap["Oscillator/PhaseShift/1"] = [&Controller](const SCmdStackItem& Item){  Controller.OnPhaseshift(1, Item.s_FloatValue); };

        // WaveFolder
        FunctionMap["WaveFolder/Fold"] = [&Controller](const SCmdStackItem& Item){ Controller.OnWaveFold(Item.s_FloatValue); };

        // LP Filter
        FunctionMap["LPFilter/Cutoff"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterCutoff(Item.s_FloatValue); };
        FunctionMap["LPFilter/Poles"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterPoles(Item.s_IntValue); };
        FunctionMap["LPFilter/Q"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterFeedback(Item.s_FloatValue); };

        // NonLinearShaper
        FunctionMap["NonLinearShaper/Cubic"] = [&Controller](const SCmdStackItem& Item){ Controller.OnNonLinearShaperA(Item.s_FloatValue); };
        FunctionMap["NonLinearShaper/Quadratic"] = [&Controller](const SCmdStackItem& Item){ Controller.OnNonLinearShaperB(Item.s_FloatValue); };
        FunctionMap["NonLinearShaper/PreGain"] = [&Controller](const SCmdStackItem& Item){ Controller.OnNonLinearShaperPreGain(Item.s_FloatValue); };

        // StepSequencer
        FunctionMap["StepSequencer/BeatsPerMinute"] = [&Controller](const SCmdStackItem& Item){ Controller.SetBeatsPerMinute(Item.s_FloatValue); };
        FunctionMap["StepSequencer/BarsPerBeat"] = [&Controller](const SCmdStackItem& Item){ Controller.SetBarsPerBeat(Item.s_IntValue); };
        FunctionMap["StepSequencer/Go"] = [&Controller](const SCmdStackItem& Item){ if(Item.s_BoolValue) { Controller.Start(); } else {Controller.Stop(); } };
        for(int Step = 0; Step<Controller.NumSteps(); ++Step)
        {
            FunctionMap["StepSequencer/Active/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetActive(Step, Item.s_BoolValue); };
            FunctionMap["StepSequencer/Note/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetNote(Step, static_cast<ENote>(Item.s_IntValue)); };
            FunctionMap["StepSequencer/Octave/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetOctave(Step, static_cast<EOctave>(Item.s_IntValue)); };
        }

        // LFO bank
        FunctionMap["LFOBank/0/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(0, Item.s_FloatValue); };
        FunctionMap["LFOBank/0/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(0, Item.s_IntValue); };
        FunctionMap["LFOBank/1/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(1, Item.s_FloatValue); };
        FunctionMap["LFOBank/1/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(0, Item.s_IntValue); };

        // FeedbackDelay
        FunctionMap["Delay/DelayMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayMilliSeconds(Item.s_FloatValue); };
        FunctionMap["Delay/Feedback"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayFeedback(Item.s_FloatValue); };
        FunctionMap["Delay/WetDry"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayWetDry(Item.s_FloatValue); };

        // AR envelope
        FunctionMap["Envelope/AR/0/AttackMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnEnvelopeAttack(Item.s_FloatValue); };
        FunctionMap["Envelope/AR/0/ReleaseMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnEnvelopeRelease(Item.s_FloatValue); };


        return FunctionMap;
    }

    CmdStack BuildDefaultCommandStack()
    {
        CmdStack Stack;

        // Oscillator
        Stack.push_back({"Oscillator/Combinor", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Sync", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Amplitude/0", false, 0, 0.50f});
        Stack.push_back({"Oscillator/Amplitude/1", false, 0, 0.50f});
        Stack.push_back({"Oscillator/Fold/0", false, 0, 0.97f});
        Stack.push_back({"Oscillator/Fold/1", false, 0, 0.97f});
        Stack.push_back({"Oscillator/FoldModAmt/0", false, 0, 0.00f});
        Stack.push_back({"Oscillator/FoldModAmt/1", false, 0, 0.00f});
        Stack.push_back({"Oscillator/Operator/0", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Operator/1", false, 0, 0.0f});
        Stack.push_back({"Oscillator/FrequencyMultiplier/0", false, 0, 1.00f});
        Stack.push_back({"Oscillator/FrequencyMultiplier/1", false, 0, 1.00f});
        Stack.push_back({"Oscillator/PhaseShift/0", false, 0, 0.00f});
        Stack.push_back({"Oscillator/PhaseShift/1", false, 0, 0.00f});

        // WaveFolder
        Stack.push_back({"WaveFolder/Fold", false, 0, 0.97f});

        // LP Filter
        Stack.push_back({"LPFilter/Cutoff", false, 0, 1.00f});
        Stack.push_back({"LPFilter/Poles", false, 1, 0.0f});
        Stack.push_back({"LPFilter/Q", false, 0, 0.00f});

        // NonLinearShaper
        Stack.push_back({"NonLinearShaper/Cubic", false, 0, 0.00f});
        Stack.push_back({"NonLinearShaper/Quadratic", false, 0, 0.00f});
        Stack.push_back({"NonLinearShaper/PreGain", false, 0, 1.00f});

        // StepSequencer
        Stack.push_back({"StepSequencer/BeatsPerMinute", false, 0, 120.0f});
        Stack.push_back({"StepSequencer/BarsPerBeat", false, 2, 0.0f});
        Stack.push_back({"StepSequencer/Go", false, 0, 0.0f});
        for(int Step = 0; Step<8; ++Step)
        {
            Stack.push_back({"StepSequencer/Active/"+std::to_string(Step), false, 0, 0.0f});
            Stack.push_back({"StepSequencer/Note/"+std::to_string(Step), false, static_cast<int>(ENote::A), 0.0f });
            Stack.push_back({"StepSequencer/Octave/"+std::to_string(Step), false, 2, 0.0f});
        }

        // LFO bank
        Stack.push_front({"LFOBank/0/Frequency", false, 0, 1.0f});
        Stack.push_front({"LFOBank/0/WaveForm", false, 3, 0.0f});
        Stack.push_front({"LFOBank/1/Frequency", false, 0, 1.0f});
        Stack.push_front({"LFOBank/1/WaveForm", false, 3, 0.0f});

        // feedback delay
        Stack.push_front({"Delay/DelayMilliSeconds", false, 0, 0.0f});
        Stack.push_front({"Delay/Feedback", false, 0, 0.0f});
        Stack.push_front({"Delay/WetDry", false, 0, 0.0f});

        // AR envelope
        Stack.push_front({"Envelope/AR/0/AttackMilliSeconds", false, 0, 10.0f});
        Stack.push_front({"Envelope/AR/0/ReleaseMilliSeconds", false, 0, 20.0f});

        return Stack;
    }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_Controller(0)
  , m_MidiInput(0)
  , m_ScopeWidget(0)
{
    ui->setupUi(this);

    QScope* Scope = new QScope(this);
    m_Controller = new CSynth8Controller(*Scope, SamplingFrequency);
    m_MidiInputHandler = new CNoteQueueMidiInputHandler(*m_Controller);
    m_MidiInput = new CMidiInput(*m_MidiInputHandler);
    m_CommandStackController = new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack());

    // build gui
    guiutils::AddLFOBank(ui->groupBox_Operator, this, m_Controller->LFOBankSize(), "LFOBank", *m_CommandStackController);
    guiutils::AddCombinedFoldedOperatorStage(ui->groupBox_Operator, this, "Oscillator", *m_CommandStackController);
    m_ScopeWidget = new QScopeWidget(*m_Controller, this);
    connect(Scope, SIGNAL(SignalSample(QVector<std::int16_t>)), m_ScopeWidget, SLOT(OnSample(QVector<std::int16_t>)));
    ui->groupBox_Operator->layout()->addWidget(m_ScopeWidget);

    guiutils::AddFeedbackDelay(ui->groupBox_Shaping, this, "Delay", *m_CommandStackController);
    guiutils::AddNonLinearShaper(ui->groupBox_Shaping, this, "NonLinearShaper", *m_CommandStackController);
    guiutils::AddLPFilter(ui->groupBox_Shaping, this, "LPFilter", *m_CommandStackController);
    guiutils::AddWaveFolder(ui->groupBox_Shaping, this, "WaveFolder", *m_CommandStackController);
    guiutils::AddAREnvelope(ui->groupBox_Shaping, this, "Envelope/AR/0", *m_CommandStackController);

    ui->groupBox_Keyboard->layout()->addWidget(new QKeyboardWidget(*m_Controller, this));
    guiutils::AddStepSequencer(ui->groupBox_Keyboard, this, m_Controller->NumSteps(), "StepSequencer", *m_CommandStackController);

    ui->groupBox_AudioDevice->layout()->addWidget(new QAudioDeviceWidget(*m_Controller, SamplingFrequency, this));
    ui->groupBox_AudioDevice->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_MidiInput->Open("Synth8", "MidiIn");
}

MainWindow::~MainWindow()
{
    m_MidiInput->Close();

    delete ui;
    delete m_ScopeWidget;
    delete m_CommandStackController;
    delete m_MidiInput;
    delete m_MidiInputHandler;
    delete m_Controller;
}
