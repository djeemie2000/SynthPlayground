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
        FunctionMap["Delay/DelayMilliSeconds"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayMilliSeconds(Item.s_FloatValue); };
        FunctionMap["Delay/Feedback"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayFeedback(Item.s_FloatValue); };
        FunctionMap["Delay/WetDry"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayWetDry(Item.s_FloatValue); };
        FunctionMap["Delay/Bypass"] = [&Controller](const SCmdStackItem& Item){  Controller.OnDelayBypass(Item.s_BoolValue); };

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
        Stack.push_back({"Delay/DelayMilliSeconds", false, 0, 250.0f});
        Stack.push_back({"Delay/Feedback", false, 0, 0.5f});
        Stack.push_back({"Delay/WetDry", false, 0, 0.0f});
        Stack.push_back({"Delay/Bypass", true, 0, 0.0f});

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
    guiutils::AddFeedbackDelay(ui->groupBox_Fx, this, "Delay", *m_CommandStackController);
    // TODO pre gain

    ui->groupBox_AudioDevice->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenAudioFilter("In", "Out", m_Controller);
    m_AudioOutput->ActivateClient();
//    m_MidiInput->Open("EffectsApp", "MidiIn");
}

MainWindow::~MainWindow()
{
    //m_MidiInput->Close();
    m_AudioOutput->CloseClient();

    delete ui;
}
