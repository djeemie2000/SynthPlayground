#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RingSequencerController.h"
#include "JackIOManager.h"
#include "GuiItems.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"
#include "JackMidiSource.h"

namespace
{
    void AddCommand(const SCmdStackItem& Item, CmdFunction Function, CmdFunctionMap& FunctionMap, CmdStack& Stack)
    {
        Stack.push_back(Item);
        FunctionMap[Item.s_Name] = Function;
    }

    CCommandStackController* BuildCommands(CRingSequencerController& Controller)
    {
        CmdFunctionMap FunctionMap;
        CmdStack DefaultStack;

        AddCommand({"RingSequencer/BeatsPerMinute", false, 0, 120.0f}, [&Controller](const SCmdStackItem& Item){ Controller.SetBeatsPerMinute(Item.s_FloatValue); }, FunctionMap, DefaultStack);
        AddCommand({"RingSequencer/BarsPerBeat", false, 2, 0.0f}, [&Controller](const SCmdStackItem& Item){ Controller.SetBarsPerBeat(Item.s_IntValue); }, FunctionMap, DefaultStack);
        AddCommand({"RingSequencer/Go", false, 0, 0.0f}, [&Controller](const SCmdStackItem& Item){ Controller.Activate(Item.s_BoolValue); }, FunctionMap, DefaultStack);

        for(int Step = 0; Step<8; ++Step)
        {
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/MidiController", false, -1, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetMidiController(Step, Item.s_IntValue); }, FunctionMap, DefaultStack);
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/Step", false, 1, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetStep(Step, Item.s_IntValue); }, FunctionMap, DefaultStack);
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/Active", false, 0, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetActive(Step, Item.s_BoolValue); }, FunctionMap, DefaultStack);
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/Start", false, 64, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetStart(Step, Item.s_IntValue); }, FunctionMap, DefaultStack);
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/Min", false, 0, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetMin(Step, Item.s_IntValue); }, FunctionMap, DefaultStack);
            AddCommand({"RingSequencer/"+std::to_string(Step)+"/Max", false, 128, 0.0f}, [&Controller, Step](const SCmdStackItem& Item){ Controller.SetMax(Step, Item.s_IntValue); }, FunctionMap, DefaultStack);
        }

        return new CCommandStackController(FunctionMap, DefaultStack);
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
    m_AudioOutput->OpenClient("RingSequencer");

    std::shared_ptr<CJackMidiSource> MidiSource(new CJackMidiSource());
    m_Controller.reset(new CRingSequencerController(m_AudioOutput->SamplingFrequency(), MidiSource, MidiSource));
    m_CommandStackController.reset(BuildCommands(*m_Controller));

    // build gui
    ui->groupBox_RingSequencer->setLayout(new QVBoxLayout());
    guiutils::AddRingSequencer(ui->groupBox_RingSequencer, this, 8, "RingSequencer", *m_CommandStackController);

    ui->groupBox_RingSequencer->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));

    m_AudioOutput->OpenMidiOutput("MidiOut", m_Controller);
    m_AudioOutput->ActivateClient();
}

MainWindow::~MainWindow()
{
    m_AudioOutput->CloseClient();

    delete ui;
}
