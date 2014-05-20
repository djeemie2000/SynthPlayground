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
#include "Controller.h"
#include "SelectableCombinorFactory.h"
#include "SelectableOperatorFactory.h"

#include "GuiItems.h"

namespace
{
    const int SamplingFrequency = 44100;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_AudioOutput(0)
  , m_AudioIODevice(0)
  , m_Controller(0)
{
    ui->setupUi(this);

    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        ui->comboBox_AudioDevice->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }

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

    // open current device
    m_AudioIODevice = new QAudioIODevice(m_Controller, this);
    CreateAudioOutput();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Controller;
}

void MainWindow::on_pushButton_Play_clicked()
{
    if(m_AudioOutput)
    {
        m_AudioOutput->resume();//TODO
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    if(m_AudioOutput)
    {
        m_AudioOutput->suspend();
    }
}

void MainWindow::on_horizontalSlider_AudioOutputVolume_valueChanged(int value)
{
    if(m_AudioOutput)
    {
        m_AudioOutput->setVolume(value/100.0f);
    }
}

void MainWindow::notified()
{
    qWarning() << "bytesFree = " << m_AudioOutput->bytesFree()
                   << ", " << "elapsedUSecs = " << m_AudioOutput->elapsedUSecs()
                   << ", " << "processedUSecs = " << m_AudioOutput->processedUSecs();
}

void MainWindow::handleStateChanged(QAudio::State state)
{
    qWarning() << "state = " << state;
}

void MainWindow::CreateAudioOutput()
{
    delete m_AudioOutput;
    m_AudioOutput = 0;

    // get current device info
    int index = ui->comboBox_AudioDevice->currentIndex();
    QAudioDeviceInfo DeviceInfo = ui->comboBox_AudioDevice->itemData(index).value<QAudioDeviceInfo>();
    // set required format on device
    QAudioFormat Format;
    Format.setSampleRate(SamplingFrequency);
    Format.setChannelCount(1);
    Format.setSampleSize(16);
    Format.setCodec("audio/pcm");
    Format.setByteOrder(QAudioFormat::LittleEndian);
    Format.setSampleType(QAudioFormat::SignedInt);

    if(DeviceInfo.isFormatSupported(Format))
    {
        m_AudioOutput = new QAudioOutput(DeviceInfo, Format, this);

        connect(m_AudioOutput, SIGNAL(notify()), SLOT(notified()));
        connect(m_AudioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(handleStateChanged(QAudio::State)));

        m_AudioOutput->start(m_AudioIODevice);
        m_AudioOutput->suspend();//????

        m_AudioOutput->setVolume(ui->horizontalSlider_AudioOutputVolume->value()/100.0f);
    }
    else
    {
        qWarning("Audio format not supported by device!");
    }
}

void MainWindow::on_comboBox_AudioDevice_activated(int /*index*/)
{
    // changed audio device => (re)create audio output
    CreateAudioOutput();
}
