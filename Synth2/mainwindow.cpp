#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include <QFileDialog>
#include <QTimer>
#include "QAudioIoDevice.h"
#include "Controller.h"
#include "QView.h"

namespace
{
    const int SamplingFrequency = 44100;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_AudioOutput(0)
  , m_AudioIODevice(0)
  , m_ScopeAutoGrab(false)
  , m_Controller()
{
    ui->setupUi(this);

    ui->comboBox_WaveForm->addItem("RampUp");
    ui->comboBox_WaveForm->addItem("RampDown");
    ui->comboBox_WaveForm->addItem("FullPseudoSin");
    ui->comboBox_WaveForm->addItem("PseudoSin");
    ui->comboBox_WaveForm->addItem("Square");
    ui->comboBox_WaveForm->addItem("InvSquare");
    ui->comboBox_WaveForm->addItem("NoOp");


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

    QView* View = new QView(this);
    connect(View, SIGNAL(SignalSampleRange(int,int)), this, SLOT(OnSampleRange(int,int)));
    connect(View, SIGNAL(SignalSample(QVector<std::uint8_t>)), this, SLOT(OnSample(QVector<std::uint8_t>)));

    m_Controller.reset(new CController(*View, SamplingFrequency));

    m_Controller->OnFrequency(ui->doubleSpinBox_Frequency->value());
    m_Controller->OnWaveForm(ui->comboBox_WaveForm->currentText().toStdString());

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
    QString Path = "GeneratedWaveForm";
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
    m_Controller->OnLoopingMode(CController::ELoopingMode(index));
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

void MainWindow::OnSampleSize(int /*Size*/)
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
            Scene->addLine(Offset, 128, Offset+Sample.size(), 128, Pen);

            // show min and max amplitude lines
            Scene->addLine(Offset, 0, Offset+Sample.size(), 0, QPen(Qt::red));
            Scene->addLine(Offset, 255, Offset+Sample.size(), 255, QPen(Qt::red));

            // show sample as path
            QPainterPath Path;
            Path.moveTo(Offset, 255-Sample[0]);
            int DeltaX = 1;
            for(int x = 0; x<Sample.size(); x+=DeltaX)
            {
                // value increases ~ y decreases!
                QPointF Pt(Offset+x, 255-Sample.at(x));
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
    ui->graphicsView_WaveForm->scale(1.1f, 1.0f);
}

void MainWindow::on_pushButton_ZoomOutHorizontal_clicked()
{
    ui->graphicsView_WaveForm->scale(0.9f, 1.0f);
}

void MainWindow::on_pushButton_ScopeGrab_clicked()
{
    int GrabSize = ui->spinBox_ScopeGrabSize->value();
    m_Controller->OnGrab(GrabSize);
}

void MainWindow::on_doubleSpinBox_Frequency_valueChanged(double arg1)
{
    m_Controller->OnFrequency(arg1);
}

void MainWindow::on_comboBox_WaveForm_activated(const QString &arg1)
{
    m_Controller->OnWaveForm(arg1.toStdString());
}

void MainWindow::on_doubleSpinBox_Feedback_valueChanged(double arg1)
{
    m_Controller->OnFeedback(arg1);
}

void MainWindow::on_doubleSpinBox_HardKneePhaseShapingX_valueChanged(double )
{
}

void MainWindow::on_doubleSpinBox_HardKneePhaseShapingY_valueChanged(double )
{
}

void MainWindow::on_doubleSpinBox_HardKneeWaveShapingX_valueChanged(double )
{
}

void MainWindow::on_doubleSpinBox_HardKneeWaveShapingY_valueChanged(double)
{
}

void MainWindow::on_doubleSpinBox_CenteredWaveshapingSlope_valueChanged(double )
{
}

void MainWindow::on_doubleSpinBox_CenteredWaveshapingCenter_valueChanged(double)
{
}

void MainWindow::on_checkBox_ScopeGrabRepeated_clicked(bool checked)
{
    m_ScopeAutoGrab = checked;
}

void MainWindow::on_doubleSpinBox_ModifierFrequency_valueChanged(double arg1)
{
    m_Controller->OnModifierFrequencyMultiplier(arg1);
}

void MainWindow::on_pushButton_Sync_clicked()
{
    float PhaseShift = ui->doubleSpinBox_SyncPhaseShift->value();
    m_Controller->OnSync(PhaseShift);
}
