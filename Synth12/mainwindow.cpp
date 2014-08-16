#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyboardWidget.h"
#include "QAudioDeviceWidget.h"
#include "Synth12Controller.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "AlsaMidiInput.h"
#include "MidiInputController.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"
#include <QFileDialog>
#include "GuiCommandStack.h"

namespace
{
    CmdFunctionMap BuildFunctionMap(CSynth12Controller& Controller)
    {
        CmdFunctionMap FunctionMap;

        // oscillator
        FunctionMap["Carrier/PlaybackSpeed"] = [&Controller](const SCmdStackItem& Item){ Controller.OnCarrierPlaybackSpeed(Item.s_FloatValue); };
        FunctionMap["Carrier/Reverse"] = [&Controller](const SCmdStackItem& Item){ Controller.OnCarrierReverse(Item.s_BoolValue); };

        //FunctionMap["Shaper/Strength"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperStrength(Item.s_FloatValue); };
        //FunctionMap["Shaper/Power"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperPower(Item.s_IntValue); };
        //FunctionMap["Shaper/PreGain"] = [&Controller](const SCmdStackItem& Item){  Controller.SetShaperPreGain(Item.s_FloatValue); };

        // PosNegshaper
        FunctionMap["PosNegShaper/Inverter/Mode"] = [&Controller](const SCmdStackItem& Item){  Controller.SetInverterMode(Item.s_IntValue); };
        FunctionMap["PosNegShaper/Derectifier/Mode"] = [&Controller](const SCmdStackItem& Item){  Controller.SetDerectifierMode(Item.s_IntValue); };

        // WaveFolder
        FunctionMap["WaveFolder/Fold"] = [&Controller](const SCmdStackItem& Item){ Controller.OnWaveFold(Item.s_FloatValue); };

        // LP Filter
        FunctionMap["LPFilter/Cutoff"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterCutoff(Item.s_FloatValue); };
        FunctionMap["LPFilter/Poles"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterPoles(Item.s_IntValue); };
        FunctionMap["LPFilter/Q"] = [&Controller](const SCmdStackItem& Item){ Controller.OnLPFilterFeedback(Item.s_FloatValue); };

        // Distortion
        FunctionMap["Distortion/Drive"] = [&Controller](const SCmdStackItem& Item){ Controller.OnDistortionDrive(Item.s_FloatValue); };


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

        // playback speed -> only can go [0,2]
        Controller.Add("Carrier/PlaybackSpeed", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/64.0f; });
        Controller.Link("Carrier/PlaybackSpeed", 0x49);
        // ?? use pitchwheel for slowing down??


        Controller.Add("WaveFolder/Fold", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/127.0f; });
        Controller.Link("WaveFolder/Fold", 0x5b);

        Controller.Add("LPFilter/Cutoff", [](SCmdStackItem& Item, int Value) { Item.s_FloatValue = Value/127.0f; });
        Controller.Link("LPFilter/Cutoff", 0x5d);

        // modwheel -> distortion!
        Controller.Add("Distortion/Drive", [](SCmdStackItem& Item, int Value){ Item.s_FloatValue = Value/127.0f; });
        Controller.Link("Distortion/Drive", 0x01);
    }

    CmdStack BuildDefaultCommandStack()
    {
        CmdStack Stack;

        // Oscillator
        Stack.push_back({"Carrier/PlaybackSpeed", false, 0, 1.0f});
        Stack.push_back({"Carrier/Reverse", false, 0, 0.0f});

        // Shaper
        Stack.push_back({"Shaper/Strength", false, 0, 0.0f});
        Stack.push_back({"Shaper/Power", false, 4, 0.0f});
        Stack.push_back({"Shaper/PreGain", false, 0, 1.0f});

        // PosNeg shaper
        Stack.push_back({"PosNegShaper/Inverter/Mode", false, 1, 0.0f});
        Stack.push_back({"PosNegShaper/Derectifier/Mode", false, 1, 0.0f});

        // WaveFolder
        Stack.push_back({"WaveFolder/Fold", false, 0, 0.97f});

        // LP Filter
        Stack.push_back({"LPFilter/Cutoff", false, 0, 1.00f});
        Stack.push_back({"LPFilter/Poles", false, 1, 0.0f});
        Stack.push_back({"LPFilter/Q", false, 0, 0.00f});

        // Distortion
        Stack.push_back({"Distortion/Drive", false, 0, 0.0f});

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
    m_AudioOutput->OpenClient("Synth12");

    m_Controller.reset(new CSynth12Controller(m_AudioOutput->SamplingFrequency()));
    m_CommandStackController.reset(new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack()));
    m_MidiInputController.reset(new CMidiInputController(*m_CommandStackController));
    BuildMidiControllerMap(*m_MidiInputController);
    m_MidiInput.reset(new CAlsaMidiInput(*m_MidiInputController));

    // build gui


    guiutils::AddMasterVolume(ui->groupBox_AudioDevice, this, "MasterVolume", *m_CommandStackController);
    guiutils::AddDistortion(ui->groupBox_AudioDevice, this, "Distortion", *m_CommandStackController);
    guiutils::AddLPFilter(ui->groupBox_AudioDevice, this, "LPFilter", *m_CommandStackController);
    guiutils::AddWaveFolder(ui->groupBox_AudioDevice, this, "WaveFolder", *m_CommandStackController);
    guiutils::AddPosNegShaper(ui->groupBox_AudioDevice, this, "PosNegShaper", *m_CommandStackController);

    ui->centralWidget->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    ConnectDoubleSpinbox(ui->doubleSpinBox_CarrierSpeed, this, "Carrier/PlaybackSpeed", *m_CommandStackController);
    ConnectCheckableToolButton(ui->toolButton_Carrier_Reverse, this, "Carrier/Reverse", *m_CommandStackController);

    m_AudioOutput->OpenAudioOutput("Out", m_Controller);
    m_AudioOutput->OpenMidiInput("MidiIn2", m_MidiInputController);
    m_AudioOutput->ActivateClient();
    m_MidiInput->Open("Synth12", "MidiIn");
}

MainWindow::~MainWindow()
{
    m_MidiInput->Close();
    m_AudioOutput->CloseClient();

    delete ui;
}

void MainWindow::on_toolButton_Carrier_Browse_clicked()
{
    // browse and open sample (wav)
    QString Path = QFileDialog::getOpenFileName(this, "Load sample", ui->lineEdit_Carrier->text(), "Sample (*.wav);;All Files (*)");
    if(!Path.isEmpty())
    {
        ui->lineEdit_Carrier->setText(Path);
        m_Controller->OpenCarrierWaveTable(Path.toStdString());
    }
}
