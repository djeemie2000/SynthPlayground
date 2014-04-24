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



namespace
{

void InitialiseWaveFormSelection(QComboBox* ComboBox)
{
    ComboBox->addItem("RampUp");
    ComboBox->addItem("RampDown");
    ComboBox->addItem("Triangle");
    ComboBox->addItem("FullPseudoSin");
    ComboBox->addItem("PseudoSin");
    ComboBox->addItem("Square");
    ComboBox->addItem("InvSquare");
    ComboBox->addItem("SquareWave");
    ComboBox->addItem("NoOp");
}

void InitialiseCombinorSelection(QComboBox* ComboBox)
{
    ComboBox->addItem("+L");
    ComboBox->addItem("*");
    ComboBox->addItem("M");
    ComboBox->addItem("m");
    ComboBox->addItem("|-|");
    ComboBox->addItem("DivA");
    ComboBox->addItem("DivB");
}

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  , m_AudioOutput(0)
  , m_AudioIODevice(0)
  , m_ScopeAutoGrab(true)
  , m_Controller()
{
    ui->setupUi(this);

    InitialiseCombinorSelection(ui->comboBox_Combinor);
    InitialiseWaveFormSelection(ui->comboBox_1_Operator);
    InitialiseWaveFormSelection(ui->comboBox_2_Operator);


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

    m_Controller = new CController(*View, SamplingFrequency);

    m_Controller->OnFrequency(ui->doubleSpinBox_Frequency->value());
    m_Controller->OnCombinor(ui->comboBox_Combinor->currentText().toStdString());
    m_Controller->OnOperator(0, ui->comboBox_1_Operator->currentText().toStdString());
    m_Controller->OnOperator(1, ui->comboBox_2_Operator->currentText().toStdString());

    m_AudioIODevice = new QAudioIODevice(m_Controller, this);

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

void MainWindow::on_checkBox_ScopeGrabRepeated_clicked(bool checked)
{
    m_ScopeAutoGrab = checked;
}

void MainWindow::on_spinBox_BitCrushserDepth_valueChanged(int arg1)
{
    m_Controller->OnBitCrusherDepth(arg1);
}

void MainWindow::on_spinBox_SnHPeriod_valueChanged(int arg1)
{
    m_Controller->OnSampleAndHoldPeriod(arg1);
}

void MainWindow::on_spinBox_RipplerThreshold_valueChanged(int arg1)
{
    m_Controller->OnRipplerThreshold(arg1);
}

void MainWindow::on_spinBox_RipplerStrength_valueChanged(int arg1)
{
    m_Controller->OnRipplerStrength(arg1);
}

void MainWindow::on_comboBox_Combinor_activated(const QString &arg1)
{
    m_Controller->OnCombinor(arg1.toStdString());
}

void MainWindow::on_doubleSpinBox_1_Amplitude_valueChanged(double arg1)
{
    m_Controller->OnAmplitude(0, arg1);
}

void MainWindow::on_doubleSpinBox_2_Amplitude_valueChanged(double arg1)
{
    m_Controller->OnAmplitude(1, arg1);
}

void MainWindow::on_comboBox_1_Operator_activated(const QString &arg1)
{
    m_Controller->OnOperator(0, arg1.toStdString());
}

void MainWindow::on_comboBox_2_Operator_activated(const QString &arg1)
{
    m_Controller->OnOperator(1, arg1.toStdString());
}

void MainWindow::on_doubleSpinBox_1_Frequency_valueChanged(double arg1)
{
    m_Controller->OnFrequencyMultiplier(0, arg1);
}

void MainWindow::on_doubleSpinBox_2_Frequency_valueChanged(double arg1)
{
    m_Controller->OnFrequencyMultiplier(1, arg1);
}

void MainWindow::on_doubleSpinBox_1_PhaseShift_valueChanged(double arg1)
{
    m_Controller->OnPhaseshift(0, arg1);
}

void MainWindow::on_doubleSpinBox_2_PhaseShift_valueChanged(double arg1)
{
    m_Controller->OnPhaseshift(1, arg1);
}

void MainWindow::on_pushButton_DetuneSync_clicked()
{
    m_Controller->OnSync();
}

void MainWindow::on_pushButton_KeyBoard_C_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::C, Octave);
}

void MainWindow::on_pushButton_Keyboard_Csharp_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::Csharp, Octave);
}

void MainWindow::on_pushButton_Keyboard_D_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::D, Octave);
}

void MainWindow::on_pushButton_Keyboard_Dsharp_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::Dsharp, Octave);
}

void MainWindow::on_pushButton_Keyboard_E_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::E, Octave);
}

void MainWindow::on_pushButton_Keyboard_F_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::F, Octave);
}

void MainWindow::on_pushButton_Keyboard_Fsharp_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::Fsharp, Octave);
}

void MainWindow::on_pushButton_Keyboard_G_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::G, Octave);
}

void MainWindow::on_pushButton_Keyboard_Gsharp_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::Gsharp, Octave);
}

void MainWindow::on_pushButton_KeyboardA_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::A, Octave);
}

void MainWindow::on_pushButton_Keyboard_Asharp_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::Asharp, Octave);
}

void MainWindow::on_pushButton_Keyboard_B_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value());
    m_Controller->OnNoteOn(ENote::B, Octave);
}

void MainWindow::on_pushButton_Keyboard_CPlusOneOctave_clicked()
{
    EOctave Octave = static_cast<EOctave>(ui->spinBox_Octave->value()+1);
    m_Controller->OnNoteOn(ENote::C, Octave);
}

void MainWindow::on_doubleSpinBox_WaveFold_valueChanged(double arg1)
{
    m_Controller->OnWaveFold(arg1);
}
