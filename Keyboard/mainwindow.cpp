#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyboardWidget.h"
#include "keyboardcontroller.h"
#include "JackIOManager.h"
#include "JackMidiSource.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_JackIOManager()
  , m_Controller()
  , m_KeyboardWidget(0)
{
    ui->setupUi(this);

    m_JackIOManager.reset(new CJackIOManager());
    m_JackIOManager->OpenClient("Keyboard");

    std::shared_ptr<CJackMidiSource> JackMidiSource(new CJackMidiSource());
    m_Controller.reset(new CKeyboardController(JackMidiSource));

    m_KeyboardWidget = new QKeyboardWidget(*m_Controller, this);
    ui->groupBox_Keyboard->layout()->addWidget(m_KeyboardWidget);

    m_JackIOManager->OpenMidiOutput("MidiOut", JackMidiSource);
    m_JackIOManager->ActivateClient();
}

MainWindow::~MainWindow()
{
    m_JackIOManager->CloseClient();

    delete ui;
}
