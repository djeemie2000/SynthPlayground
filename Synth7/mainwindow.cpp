#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QTimer>
#include <QDebug>
#include "QAudioIoDevice.h"
#include "QView.h"
#include "QKeyboardWidget.h"
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
  , m_ScopeAutoGrab(true)
  , m_Controller(0)
{
    ui->setupUi(this);

    QGraphicsScene* Scene = new QGraphicsScene(this);
    ui->graphicsView_WaveForm->setScene(Scene);

    Scene->setForegroundBrush(QColor(0,0,0,92));

    ui->graphicsView_WaveForm->show();

    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        ui->comboBox_AudioDevice->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    timer->start(1000);

    QScope* View = new QScope(this);
    connect(View, SIGNAL(SignalSample(QVector<std::int16_t>)), this, SLOT(OnSample(QVector<std::int16_t>)));

    m_Controller = new CController(*View, SamplingFrequency);

    m_AudioIODevice = new QAudioIODevice(m_Controller, this);

    // build gui
    guiutils::AddNonLinearShaper(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddLPFilter(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddWaveFolder(ui->groupBox_Shaping, this, *m_Controller);
    guiutils::AddBitFX(ui->groupBox_Fx, this, *m_Controller);

    ui->groupBox_Synth->layout()->addWidget(new QKeyboardWidget(*m_Controller, this));

    guiutils::AddStepSequencer(ui->groupBox_Synth, this, *m_Controller);

    guiutils::AddOperatorStage(ui->groupBox_Operator, this, *m_Controller);

    // open current device
    CreateAudioOutput();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Controller;
}

void MainWindow::on_pushButton_Play_clicked()
{
    m_Controller->OnPlay();
    if(m_AudioOutput)
    {
        m_AudioOutput->resume();//TODO
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{
    m_Controller->OnStop();
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

void MainWindow::OnTimer()
{
    if(m_ScopeAutoGrab)
    {
        int GrabSize = ui->spinBox_ScopeGrabSize->value();
        m_Controller->OnGrab(GrabSize);
    }
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

void MainWindow::OnSampleSize(int /*Size*/)
{
    //TODO?
}

void MainWindow::OnSample(QVector<std::int16_t> Sample)
{
    //qWarning() << "Recieved sample! size= " << Sample.size();

    if(!Sample.empty())
    {
        if(QGraphicsScene* Scene = ui->graphicsView_WaveForm->scene())
        {
            // clear all previous items
            QList<QGraphicsItem*> Items = Scene->items();
            for(auto Item : Items)
            {
                Scene->removeItem(Item);
            }

            // center around 'middle' of sample
            int Offset = -Sample.size()/2;

            // show red line as x axis
            QPen Pen(Qt::red);
            Pen.setWidth(3);
            Scene->addLine(Offset, 0, Offset+Sample.size(), 0, Pen);

            // show min and max amplitude lines
            Scene->addLine(Offset, -127, Offset+Sample.size(), -127, QPen(Qt::red));
            Scene->addLine(Offset, 127, Offset+Sample.size(), 127, QPen(Qt::red));

            // show sample as path
            QPainterPath Path;
            Path.moveTo(Offset, -Sample[0]/256);
            int DeltaX = 1;
            for(int x = 0; x<Sample.size(); x+=DeltaX)
            {
                // value increases ~ y decreases!
                QPointF Pt(Offset+x, -Sample.at(x)/256);
                Path.lineTo(Pt);
            }
            Scene->addPath(Path, QPen(Qt::green));

        }
        else
        {
            qWarning() << "No graphics scene! ";
        }
    }
}

void MainWindow::on_pushButton_ZoomInHorizontal_clicked()
{
    ui->graphicsView_WaveForm->scale(1.1f, 1.1f);
}

void MainWindow::on_pushButton_ZoomOutHorizontal_clicked()
{
    ui->graphicsView_WaveForm->scale(0.9f, 0.9f);
}

void MainWindow::on_pushButton_ScopeGrab_clicked()
{
    int GrabSize = ui->spinBox_ScopeGrabSize->value();
    m_Controller->OnGrab(GrabSize);
}

void MainWindow::on_checkBox_ScopeGrabRepeated_clicked(bool checked)
{
    m_ScopeAutoGrab = checked;
}
