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
#include "Controller.h"
#include "GuiItems.h"

namespace
{
    const int SamplingFrequency = 44100;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_Controller(0)
{
    ui->setupUi(this);


    QScope* Scope = new QScope(this);
    m_Controller = new CController(*Scope, SamplingFrequency);

    // build gui
    guiutils::AddOperatorStage(ui->groupBox_Operator, this, *m_Controller);
    QScopeWidget* ScopeWidget = new QScopeWidget(*m_Controller, this);
    connect(Scope, SIGNAL(SignalSample(QVector<std::int16_t>)), ScopeWidget, SLOT(OnSample(QVector<std::int16_t>)));
    ui->groupBox_Operator->layout()->addWidget(ScopeWidget);

    guiutils::AddBitFX(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddNonLinearShaper(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddLPFilter(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddWaveFolder(ui->groupBox_Shaping, this, *m_Controller);

    ui->groupBox_Keyboard->layout()->addWidget(new QKeyboardWidget(*m_Controller, this));
    guiutils::AddStepSequencer(ui->groupBox_Keyboard, this, *m_Controller);

    ui->groupBox_AudioDevice->layout()->addWidget(new QAudioDeviceWidget(*m_Controller, SamplingFrequency, this));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Controller;
}
