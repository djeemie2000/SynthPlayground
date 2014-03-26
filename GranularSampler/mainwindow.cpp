#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QFileDialog>
#include "QAudioIoDevice.h"
#include "GranularsamplerController.h"
#include "QGranularSamplerView.h"

namespace
{
    const int SamplingFrequency = 44100;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  //, m_Scene(0)
  , m_AudioOutput(0)
  , m_Controller()
{
    ui->setupUi(this);

    QGraphicsScene* Scene = new QGraphicsScene(this);
    ui->graphicsView_WaveForm->setScene(Scene);

    Scene->setForegroundBrush(QColor(0,0,127,92));

    ui->graphicsView_WaveForm->show();

    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        ui->comboBox_AudioDevice->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }

    QGranularSamplerView* View = new QGranularSamplerView(this);
    connect(View, SIGNAL(SignalSampleRange(int,int)), this, SLOT(OnSampleRange(int,int)));
    connect(View, SIGNAL(SignalSample(QVector<std::uint8_t>)), this, SLOT(OnSample(QVector<std::uint8_t>)));

    m_Controller.reset(new CGranularSamplerController(*View, SamplingFrequency));

    m_AudioIODevice = new QAudioIODevice(m_Controller.get(), this);

    // open current device
    CreateAudioOutput();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Open_clicked()
{
    if(m_AudioOutput)
    {
        m_AudioOutput->suspend();
    }
    //TODO open file dialog -> path in lineedit, pass path to controller
    QString Path = QFileDialog::getOpenFileName(this);
    if(!Path.isEmpty())
    {
        ui->lineEdit_Path->setText(Path);
        m_Controller->OnOpen(Path.toStdString());
    }
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

void MainWindow::on_comboBox_LoopMode_activated(int index)
{
    m_Controller->OnLoopingMode(CGranularSamplerController::ELoopingMode(index));
}

void MainWindow::on_doubleSpinBox_Speed_valueChanged(double arg1)
{
    m_Controller->OnSpeed(arg1);
}

void MainWindow::on_horizontalSlider_BeginPosition_valueChanged(int value)
{
    int Begin = value;
    int End = Begin + ui->spinBox_Duration->value();
    ui->horizontalSlider_EndPosition->setValue(End);

    m_Controller->OnInterval(Begin, End);
}

void MainWindow::on_horizontalSlider_EndPosition_valueChanged(int value)
{
    int End = value;
    int Begin = End - ui->spinBox_Duration->value();

    m_Controller->OnInterval(Begin, End);
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
    Format.setSampleSize(8);
    Format.setCodec("audio/pcm");
    Format.setByteOrder(QAudioFormat::LittleEndian);
    Format.setSampleType(QAudioFormat::UnSignedInt);

    if(DeviceInfo.isFormatSupported(Format))
    {
        m_AudioOutput = new QAudioOutput(DeviceInfo, Format, this);

        connect(m_AudioOutput, SIGNAL(notify()), SLOT(notified()));
        connect(m_AudioOutput, SIGNAL(stateChanged(QAudio::State)), SLOT(handleStateChanged(QAudio::State)));

        m_AudioOutput->start(m_AudioIODevice);
        m_AudioOutput->suspend();//????
    }
    else
    {
        qWarning("Audio format not supported by device!");
    }
    ui->horizontalSlider_AudioOutputVolume->setValue(50);//triggers ??
    on_horizontalSlider_AudioOutputVolume_valueChanged(50);// needed??
}

void MainWindow::on_comboBox_AudioDevice_activated(int /*index*/)
{
    // changed audio device => (re)create audio output
    CreateAudioOutput();
}

void MainWindow::on_spinBox_Duration_valueChanged(int arg1)
{
    int Begin = ui->horizontalSlider_BeginPosition->value();
    int End = Begin + arg1;
    ui->horizontalSlider_EndPosition->setValue(End);

    m_Controller->OnInterval(Begin, End);
}

void MainWindow::OnSampleRange(int Begin, int End)
{
    ui->horizontalSlider_BeginPosition->setRange(Begin, End);
    ui->horizontalSlider_EndPosition->setRange(Begin, End);
    ui->horizontalSlider_BeginPosition->setValue(Begin);
    ui->horizontalSlider_EndPosition->setValue(End);
    ui->spinBox_Duration->setRange(0, End-Begin);
    ui->spinBox_Duration->setValue(End-Begin);
}

void MainWindow::OnSampleSize(int Size)
{
    //TODO?
}

void MainWindow::OnSample(QVector<std::uint8_t> Sample)
{
    qWarning() << "Recieved sample! size= " << Sample.size();

    if(!Sample.empty())
    {
        if(QGraphicsScene* Scene = ui->graphicsView_WaveForm->scene())
        {
            // center around 'middle' of sample
            int Offset = -Sample.size()/2;

            // show red line as x axis
            QPen Pen(Qt::red);
            Pen.setWidth(3);
            Scene->addLine(Offset, 128, Offset+Sample.size(), 128, Pen);

            // show min and max amplitude lines
            Scene->addLine(Offset, 0, Offset+Sample.size(), 0, QPen(Qt::red));
            Scene->addLine(Offset, 255, Offset+Sample.size(), 255, QPen(Qt::red));

            // show sample as path
            QPainterPath Path;
            Path.moveTo(Offset, Sample[0]);
            int DeltaX = 4;
            for(int x = 0; x<Sample.size(); x+=DeltaX)
            {
                Path.lineTo(QPointF(Offset+x, Sample.at(x)));
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
    ui->graphicsView_WaveForm->scale(1.1f, 1.0f);
}

void MainWindow::on_pushButton_ZoomOutHorizontal_clicked()
{
    ui->graphicsView_WaveForm->scale(0.9f, 1.0f);
}
