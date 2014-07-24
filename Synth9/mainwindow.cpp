#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyboardWidget.h"
#include "QAudioDeviceWidget.h"
#include "Synth9Controller.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "AlsaMidiInput.h"
#include "MidiInputController.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"

namespace
{
    CmdFunctionMap BuildFunctionMap(CSynth9Controller& Controller)
    {
        CmdFunctionMap FunctionMap;

        // oscillator (combined folded operator stage)
        FunctionMap["Oscillator/Carrier/Select"] = [&Controller](const SCmdStackItem& Item){  Controller.OnCarrier(Item.s_IntValue); };
        FunctionMap["Oscillator/Modulator/Select"] = [&Controller](const SCmdStackItem& Item){  Controller.OnModulator(Item.s_IntValue); };
        FunctionMap["Oscillator/Sync"] = [&Controller](const SCmdStackItem& ){  Controller.OnSync(); };
        FunctionMap["Oscillator/Modulator/Amplitude"] = [&Controller](const SCmdStackItem& Item){  Controller.OnModulatorAmplitude(Item.s_FloatValue); };
        FunctionMap["Oscillator/Modulator/AmplitudeModAmt"] = [&Controller](const SCmdStackItem& Item){  Controller.OnModulatorAmplitudeModAmount(Item.s_FloatValue); };
        FunctionMap["Oscillator/Modulator/PhaseShift"] = [&Controller](const SCmdStackItem& Item){  Controller.OnModulatorPhaseshift(Item.s_FloatValue); };
        FunctionMap["Oscillator/Modulator/FrequencyMultiplier"] = [&Controller](const SCmdStackItem& Item){  Controller.OnModulatorFrequencyMultiplier(Item.s_FloatValue); };
        FunctionMap["Oscillator/Oscillator/Select"] = [&Controller](const SCmdStackItem& Item){  Controller.OnOscillator(Item.s_IntValue); };

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
        FunctionMap["StepSequencer/NumSteps"] = [&Controller](const SCmdStackItem& Item){ Controller.SetNumSteps(Item.s_IntValue); };
        for(int Step = 0; Step<Controller.GetMaxNumSteps(); ++Step)
        {
            FunctionMap["StepSequencer/Active/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetActive(Step, Item.s_BoolValue); };
            FunctionMap["StepSequencer/Note/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetNote(Step, static_cast<ENote>(Item.s_IntValue)); };
            FunctionMap["StepSequencer/Octave/"+std::to_string(Step)] = [&Controller,Step](const SCmdStackItem& Item){ Controller.SetOctave(Step, static_cast<EOctave>(Item.s_IntValue)); };
        }

        // LFO bank
        FunctionMap["LFOBank/0/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(0, Item.s_FloatValue); };
        FunctionMap["LFOBank/0/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(0, Item.s_IntValue); };
        FunctionMap["LFOBank/1/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(1, Item.s_FloatValue); };
        FunctionMap["LFOBank/1/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(1, Item.s_IntValue); };

        // FeedbackDelay
        FunctionMap["Delay/DelayMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayMilliSeconds(Item.s_FloatValue); };
        FunctionMap["Delay/Feedback"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayFeedback(Item.s_FloatValue); };
        FunctionMap["Delay/WetDry"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayWetDry(Item.s_FloatValue); };
        FunctionMap["Delay/Bypass"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayBypass(Item.s_BoolValue); };

        // AR envelope
        FunctionMap["Envelope/AR/0/AttackMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnEnvelopeAttack(Item.s_FloatValue); };
        FunctionMap["Envelope/AR/0/ReleaseMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnEnvelopeRelease(Item.s_FloatValue); };

        // master volume
        FunctionMap["MasterVolume"] = [&Controller](const SCmdStackItem& Item){  Controller.SetMasterVolume(Item.s_FloatValue); };

        // Midi note on/off
        FunctionMap["Midi/NoteOn"] = [&Controller](const SCmdStackItem& Item){  Controller.OnNoteOn(Item.s_IntValue & 0x000000FF, Item.s_IntValue >> 8, Item.s_TimeStamp);  };
        FunctionMap["Midi/NoteOff"] = [&Controller](const SCmdStackItem& Item){  Controller.OnNoteOff(Item.s_IntValue & 0x000000FF, Item.s_IntValue >> 8, Item.s_TimeStamp);  };

        return FunctionMap;
    }

    void BuildMidiControllerMap(CMidiInputController& Controller)
    {
        Controller.Add("MasterVolume", [](SCmdStackItem& Item, int Value){ Item.s_FloatValue = Value/127.0f;  });
        Controller.Link("MasterVolume", 7);
    }

    CmdStack BuildDefaultCommandStack()
    {
        CmdStack Stack;

        // Oscillator
//        Stack.push_back({"Oscillator/Combinor", false, 0, 0.0f});
//        Stack.push_back({"Oscillator/Sync", false, 0, 0.0f});
//        Stack.push_back({"Oscillator/Amplitude/0", false, 0, 0.50f});
//        Stack.push_back({"Oscillator/Amplitude/1", false, 0, 0.50f});
//        Stack.push_back({"Oscillator/Fold/0", false, 0, 0.97f});
//        Stack.push_back({"Oscillator/Fold/1", false, 0, 0.97f});
//        Stack.push_back({"Oscillator/FoldModAmt/0", false, 0, 0.00f});
//        Stack.push_back({"Oscillator/FoldModAmt/1", false, 0, 0.00f});
//        Stack.push_back({"Oscillator/Operator/0", false, 0, 0.0f});
//        Stack.push_back({"Oscillator/Operator/1", false, 0, 0.0f});
//        Stack.push_back({"Oscillator/FrequencyMultiplier/0", false, 0, 1.00f});
//        Stack.push_back({"Oscillator/FrequencyMultiplier/1", false, 0, 1.00f});
//        Stack.push_back({"Oscillator/PhaseShift/0", false, 0, 0.00f});
//        Stack.push_back({"Oscillator/PhaseShift/1", false, 0, 0.00f});

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
        Stack.push_back({"StepSequencer/NumSteps", false, 8, 0.0f});
        for(int Step = 0; Step<8; ++Step)
        {
            Stack.push_back({"StepSequencer/Active/"+std::to_string(Step), false, 0, 0.0f});
            Stack.push_back({"StepSequencer/Note/"+std::to_string(Step), false, static_cast<int>(ENote::A), 0.0f });
            Stack.push_back({"StepSequencer/Octave/"+std::to_string(Step), false, 2, 0.0f});
        }

        // LFO bank
        Stack.push_back({"LFOBank/0/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/0/WaveForm", false, 3, 0.0f});
        Stack.push_back({"LFOBank/1/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/1/WaveForm", false, 3, 0.0f});

        // feedback delay
        Stack.push_back({"Delay/DelayMilliSeconds", false, 0, 250.0f});
        Stack.push_back({"Delay/Feedback", false, 0, 0.5f});
        Stack.push_back({"Delay/WetDry", false, 0, 0.0f});
        Stack.push_back({"Delay/Bypass", true, 0, 0.0f});

        // AR envelope
        Stack.push_back({"Envelope/AR/0/AttackMilliSeconds", false, 0, 10.0f});
        Stack.push_back({"Envelope/AR/0/ReleaseMilliSeconds", false, 0, 20.0f});

        // master volume
        Stack.push_back({"MasterVolume", false, 0, 1.0f});

        return Stack;
    }
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_AudioOutput()
  , m_Controller()
  , m_MidiInput(0)
{
    ui->setupUi(this);

    m_AudioOutput.reset(new CJackIOManager());
    m_AudioOutput->OpenClient("Synth9");

    m_Controller.reset(new CSynth9Controller(m_AudioOutput->SamplingFrequency()));
    m_CommandStackController.reset(new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack()));
    m_MidiInputController.reset(new CMidiInputController(*m_CommandStackController));
    BuildMidiControllerMap(*m_MidiInputController);
    m_MidiInput.reset(new CAlsaMidiInput(*m_MidiInputController));

    // build gui
    guiutils::AddLFOBank(ui->groupBox_Operator, this, m_Controller->LFOBankSize(), "LFOBank", *m_CommandStackController);
    guiutils::AddFMOperatorStage(ui->groupBox_Operator, this, "Oscillator", *m_CommandStackController);

    guiutils::AddMasterVolume(ui->groupBox_Fx, this, "MasterVolume", *m_CommandStackController);
    guiutils::AddFeedbackDelay(ui->groupBox_Fx, this, "Delay", *m_CommandStackController);
    guiutils::AddNonLinearShaper(ui->groupBox_Shaping, this, "NonLinearShaper", *m_CommandStackController);
    guiutils::AddLPFilter(ui->groupBox_Shaping, this, "LPFilter", *m_CommandStackController);
    guiutils::AddWaveFolder(ui->groupBox_Shaping, this, "WaveFolder", *m_CommandStackController);
    guiutils::AddAREnvelope(ui->groupBox_Shaping, this, "Envelope/AR/0", *m_CommandStackController);

    ui->groupBox_Keyboard->layout()->addWidget(new QKeyboardWidget(*m_Controller, this));
    guiutils::AddStepSequencer(ui->groupBox_Keyboard, this, m_Controller->GetMaxNumSteps(), "StepSequencer", *m_CommandStackController);

    ui->groupBox_AudioDevice->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenAudioOutput("Out", m_Controller);
    m_AudioOutput->OpenMidiInput("MidiIn2", m_MidiInputController);
    m_AudioOutput->ActivateClient();
    m_MidiInput->Open("Synth9", "MidiIn");
}

MainWindow::~MainWindow()
{
    m_MidiInput->Close();
    m_AudioOutput->CloseClient();

    delete ui;
}
