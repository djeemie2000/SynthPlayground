#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyboardWidget.h"
#include "QAudioDeviceWidget.h"
#include "Synth11Controller.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "AlsaMidiInput.h"
#include "MidiInputController.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"

namespace
{
    CmdFunctionMap BuildFunctionMap(CSynth11Controller& Controller)
    {
        CmdFunctionMap FunctionMap;

        // oscillator
        FunctionMap["Oscillator/Operator1/Select"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectOperator1(Item.s_IntValue); };
        FunctionMap["Oscillator/Operator2/Select"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectOperator2(Item.s_IntValue); };
        FunctionMap["Oscillator/Mix"] = [&Controller](const SCmdStackItem& Item){  Controller.SetMix(Item.s_FloatValue); };
        FunctionMap["Oscillator/MixModAmt"] = [&Controller](const SCmdStackItem& Item){  Controller.SetMixModAmt(Item.s_FloatValue); };
        FunctionMap["Oscillator/Skew"] = [&Controller](const SCmdStackItem& Item){  Controller.SetSkew(Item.s_FloatValue); };
        FunctionMap["Oscillator/SkewModAmt"] = [&Controller](const SCmdStackItem& Item){  Controller.SetSkewModAmt(Item.s_FloatValue); };

        // Shaper
        FunctionMap["Shaper/Strength"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperStrength(Item.s_FloatValue); };
        FunctionMap["Shaper/Power"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperPower(Item.s_IntValue); };
        FunctionMap["Shaper/PreGain"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperPreGain(Item.s_FloatValue); };

        // WaveFolder
        FunctionMap["WaveFolder/Fold"] = [&Controller](const SCmdStackItem& Item){ Controller.OnWaveFold(Item.s_FloatValue); };

        // LP Filter
        FunctionMap["LPFilter/Cutoff"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterCutoff(Item.s_FloatValue); };
        FunctionMap["LPFilter/Poles"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterPoles(Item.s_IntValue); };
        FunctionMap["LPFilter/Q"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterFeedback(Item.s_FloatValue); };

        // LFO bank
        FunctionMap["LFOBank/0/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(0, Item.s_FloatValue); };
        FunctionMap["LFOBank/0/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(0, Item.s_IntValue); };
        FunctionMap["LFOBank/1/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(1, Item.s_FloatValue); };
        FunctionMap["LFOBank/1/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(1, Item.s_IntValue); };
        FunctionMap["LFOBank/2/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(2, Item.s_FloatValue); };
        FunctionMap["LFOBank/2/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(2, Item.s_IntValue); };
        FunctionMap["LFOBank/3/Frequency"] = [&Controller](const SCmdStackItem& Item){  Controller.SetLFOFrequency(3, Item.s_FloatValue); };
        FunctionMap["LFOBank/3/Waveform"] = [&Controller](const SCmdStackItem& Item){  Controller.SelectLFOWaveform(3, Item.s_IntValue); };

        // Distortion
        FunctionMap["Distortion/Drive"] = [&Controller](const SCmdStackItem& Item){ Controller.OnDistortionDrive(Item.s_FloatValue); };

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

        Controller.Add("Oscillator/Mix", [](SCmdStackItem& Item, int Value){ Item.s_FloatValue = Value/127.0f; });
        Controller.Link("Oscillator/Mix", 0x4a);

        Controller.Add("Oscillator/Skew", [](SCmdStackItem& Item, int Value){ Item.s_FloatValue = (Value-64)/64.0f; });
        Controller.Link("Oscillator/Skew", 0x47);

        Controller.Add("WaveFolder/Fold", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/127.0f; });
        Controller.Link("WaveFolder/Fold", 0x5b);

        Controller.Add("LPFilter/Cutoff", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/127.0f; });
        Controller.Link("LPFilter/Cutoff", 0x5d);

//        Controller.Add("WaveFolder/Fold", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value*Value*0.010f; });
//        Controller.Link("WaveFolder/Fold", 0x49);

//        Controller.Add("LPFilter/Cutoff", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/127.0f; });
//        Controller.Link("LPFilter/Cutoff", 0x48);

        Controller.Add("Envelope/AR/0/AttackMilliSeconds", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value*32; });
        Controller.Link("Envelope/AR/0/AttackMilliSeconds", 0x05);

        Controller.Add("Envelope/AR/0/ReleaseMilliSeconds", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value*32; });
        Controller.Link("Envelope/AR/0/ReleaseMilliSeconds", 0x54);

        // modwheel -> distortion!
        Controller.Add("Distortion/Drive", [](SCmdStackItem& Item, int Value){ Item.s_FloatValue = Value/127.0f; });
        Controller.Link("Distortion/Drive", 0x01);
    }

    CmdStack BuildDefaultCommandStack()
    {
        CmdStack Stack;

        // Oscillator
        Stack.push_back({"Oscillator/Operator1/Select", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Operator2/Select", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Mix", false, 0, 0.0f});
        Stack.push_back({"Oscillator/MixModAmt", false, 0, 0.0f});
        Stack.push_back({"Oscillator/Skew", false, 0, 0.0f});
        Stack.push_back({"Oscillator/SkewModAmt", false, 0, 0.0f});

        // Shaper
        Stack.push_back({"Shaper/Strength", false, 0, 0.0f});
        Stack.push_back({"Shaper/Power", false, 4, 0.0f});
        Stack.push_back({"Shaper/PreGain", false, 0, 1.0f});

        // WaveFolder
        Stack.push_back({"WaveFolder/Fold", false, 0, 0.97f});

        // LP Filter
        Stack.push_back({"LPFilter/Cutoff", false, 0, 1.00f});
        Stack.push_back({"LPFilter/Poles", false, 1, 0.0f});
        Stack.push_back({"LPFilter/Q", false, 0, 0.00f});

        // LFO bank
        Stack.push_back({"LFOBank/0/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/0/WaveForm", false, 3, 0.0f});
        Stack.push_back({"LFOBank/1/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/1/WaveForm", false, 3, 0.0f});
        Stack.push_back({"LFOBank/2/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/2/WaveForm", false, 3, 0.0f});
        Stack.push_back({"LFOBank/3/Frequency", false, 0, 1.0f});
        Stack.push_back({"LFOBank/3/WaveForm", false, 3, 0.0f});

        // Distortion
        Stack.push_back({"Distortion/Drive", false, 0, 0.0f});

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
    m_AudioOutput->OpenClient("Synth11");

    m_Controller.reset(new CSynth11Controller(m_AudioOutput->SamplingFrequency()));
    m_CommandStackController.reset(new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack()));
    m_MidiInputController.reset(new CMidiInputController(*m_CommandStackController));
    BuildMidiControllerMap(*m_MidiInputController);
    m_MidiInput.reset(new CAlsaMidiInput(*m_MidiInputController));

    // build gui
    guiutils::AddIntegerPowerShaper(ui->groupBox_Operator, this, "Shaper", *m_CommandStackController);
    guiutils::AddSimpleInterpolatingOperator(ui->groupBox_Operator, this, "Oscillator", *m_CommandStackController);

    guiutils::AddLFOBank(ui->groupBox_Shaping, this, m_Controller->LFOBankSize(), "LFOBank", *m_CommandStackController);
    guiutils::AddAREnvelope(ui->groupBox_Shaping, this, "Envelope/AR/0", *m_CommandStackController);

    guiutils::AddMasterVolume(ui->groupBox_AudioDevice, this, "MasterVolume", *m_CommandStackController);
    guiutils::AddDistortion(ui->groupBox_AudioDevice, this, "Distortion", *m_CommandStackController);
    guiutils::AddLPFilter(ui->groupBox_AudioDevice, this, "LPFilter", *m_CommandStackController);
    guiutils::AddWaveFolder(ui->groupBox_AudioDevice, this, "WaveFolder", *m_CommandStackController);
    ui->groupBox_AudioDevice->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenAudioOutput("Out", m_Controller);
    m_AudioOutput->ActivateClient();
    m_MidiInput->Open("Synth11", "MidiIn");
}

MainWindow::~MainWindow()
{
    m_MidiInput->Close();
    m_AudioOutput->CloseClient();

    delete ui;
}
