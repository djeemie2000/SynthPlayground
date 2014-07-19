#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyboardWidget.h"
#include "QAudioDeviceWidget.h"
#include "effectsappcontroller.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "AlsaMidiInput.h"
#include "MidiInputController.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"

namespace
{
    CmdFunctionMap BuildFunctionMap(CEffectsAppController& Controller)
    {
        CmdFunctionMap FunctionMap;

        // PreGain
        FunctionMap["PreGain"] = [&Controller](const SCmdStackItem& Item){  Controller.OnPreGain(Item.s_FloatValue); };

        // FeedbackDelay
        FunctionMap["Delay/Left/DelayMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayMilliSecondsLeft(Item.s_FloatValue); };
        FunctionMap["Delay/Left/Feedback"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayFeedbackLeft(Item.s_FloatValue); };
        FunctionMap["Delay/Left/WetDry"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayWetDryLeft(Item.s_FloatValue); };
        FunctionMap["Delay/Left/Bypass"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayBypassLeft(Item.s_BoolValue); };

        FunctionMap["Delay/Right/DelayMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayMilliSecondsRight(Item.s_FloatValue); };
        FunctionMap["Delay/Right/Feedback"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayFeedbackRight(Item.s_FloatValue); };
        FunctionMap["Delay/Right/WetDry"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayWetDryRight(Item.s_FloatValue); };
        FunctionMap["Delay/Right/Bypass"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayBypassRight(Item.s_BoolValue); };

        // master volume
        FunctionMap["MasterVolume"] = [&Controller](const SCmdStackItem& Item){  Controller.SetMasterVolume(Item.s_FloatValue); };


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

        // pre gain
        Stack.push_back({"PreGain", false, 0, 1.0f});

        // feedback delay
        Stack.push_back({"Delay/Left/DelayMilliSeconds", false, 0, 250.0f});
        Stack.push_back({"Delay/Left/Feedback", false, 0, 0.5f});
        Stack.push_back({"Delay/Left/WetDry", false, 0, 0.0f});
        Stack.push_back({"Delay/Left/Bypass", true, 0, 0.0f});

        Stack.push_back({"Delay/Right/DelayMilliSeconds", false, 0, 250.0f});
        Stack.push_back({"Delay/Right/Feedback", false, 0, 0.5f});
        Stack.push_back({"Delay/Right/WetDry", false, 0, 0.0f});
        Stack.push_back({"Delay/Right/Bypass", true, 0, 0.0f});

        // master volume
        Stack.push_back({"MasterVolume", false, 0, 0.5f});

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
    m_AudioOutput->OpenClient("EffectsApp");

    m_Controller.reset(new CEffectsAppController(m_AudioOutput->SamplingFrequency()));
    m_CommandStackController.reset(new CCommandStackController(BuildFunctionMap(*m_Controller), BuildDefaultCommandStack()));
    m_MidiInputController.reset(new CMidiInputController(*m_CommandStackController));
    BuildMidiControllerMap(*m_MidiInputController);
    //m_MidiInput.reset(new CAlsaMidiInput(*m_MidiInputController));

    // build gui
    guiutils::AddMasterVolume(ui->groupBox_Fx, this, "MasterVolume", *m_CommandStackController);
    guiutils::AddFeedbackDelay(ui->groupBox_Fx, this, "Delay/Left", *m_CommandStackController);
    guiutils::AddFeedbackDelay(ui->groupBox_Fx, this, "Delay/Right", *m_CommandStackController);
    // TODO pre gain

    ui->groupBox_AudioDevice->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenAudioFilter(m_Controller);
    m_AudioOutput->ActivateClient();
//    m_MidiInput->Open("EffectsApp", "MidiIn");
}

MainWindow::~MainWindow()
{
    //m_MidiInput->Close();
    m_AudioOutput->CloseClient();

    delete ui;
}
