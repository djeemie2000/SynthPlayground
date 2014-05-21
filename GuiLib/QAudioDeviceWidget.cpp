#include "QAudioDeviceWidget.h"
#include "ui_qaudiodevicewidget.h"
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QDebug>
#include "QAudioIoDevice.h"


QAudioDeviceWidget::QAudioDeviceWidget(IAudioSource &AudioSource, int SamplingFrequency, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAudioDeviceWidget)
  , m_AudioSource(AudioSource)
  , m_SamplingFrequency(SamplingFrequency)
{
    ui->setupUi(this);

    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        ui->comboBox_AudioDevice->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }

    // open current device
    m_AudioIODevice = new QAudioIODevice(m_AudioSource, this);
    CreateAudioOutput();
}

QAudioDeviceWidget::~QAudioDeviceWidget()
{
    delete ui;
}

void QAudioDeviceWidget::CreateAudioOutput()
{
    delete m_AudioOutput;
    m_AudioOutput = 0;

    // get current device info
    int index = ui->comboBox_AudioDevice->currentIndex();
    QAudioDeviceInfo DeviceInfo = ui->comboBox_AudioDevice->itemData(index).value<QAudioDeviceInfo>();
    // set required format on device
    QAudioFormat Format;
    Format.setSampleRate(m_SamplingFrequency);
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

        m_AudioOutput->setVolume(ui->horizontalSlider_Volume->value()/100.0f);
    }
    else
    {
        qWarning("Audio format not supported by device!");
    }
}

void QAudioDeviceWidget::on_pushButton_Play_clicked(bool checked)
{
    if(m_AudioOutput)
    {
        if(checked)
        {
            m_AudioOutput->resume();
        }
        else
        {
            m_AudioOutput->suspend();
        }
    }
}

void QAudioDeviceWidget::on_horizontalSlider_Volume_sliderMoved(int position)
{
    if(m_AudioOutput)
    {
        m_AudioOutput->setVolume(position/100.0f);
    }
}

void QAudioDeviceWidget::on_comboBox_AudioDevice_currentIndexChanged(const QString &arg1)
{
    // changed audio device => (re)create audio output
    CreateAudioOutput();
}

void QAudioDeviceWidget::notified()
{
    qWarning() << "bytesFree = " << m_AudioOutput->bytesFree()
                   << ", " << "elapsedUSecs = " << m_AudioOutput->elapsedUSecs()
                   << ", " << "processedUSecs = " << m_AudioOutput->processedUSecs();
}

void QAudioDeviceWidget::handleStateChanged(QAudio::State state)
{
    qWarning() << "state = " << state;
}
