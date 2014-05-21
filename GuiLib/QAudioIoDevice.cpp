#include "QAudioIoDevice.h"
#include "AudioSourceI.h"

QAudioIODevice::QAudioIODevice(IAudioSource &AudioSource, QObject *parent)
    : QIODevice(parent)
    , m_AudioSource(AudioSource)
{
    start();
}

void QAudioIODevice::start()
{
    open(QIODevice::ReadOnly);
}

void QAudioIODevice::stop()
{
    close();
}

qint64 QAudioIODevice::readData(char *data, qint64 maxlen)
{
    // ask the controller
    return m_AudioSource.OnRead(data, maxlen);
}

qint64 QAudioIODevice::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 QAudioIODevice::bytesAvailable() const
{
    return 1024 + QIODevice::bytesAvailable();
}
