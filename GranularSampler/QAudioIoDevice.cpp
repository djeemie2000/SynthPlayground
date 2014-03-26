#include "QAudioIoDevice.h"
#include "GranularSamplerController.h"

QAudioIODevice::QAudioIODevice(CGranularSamplerController* Controller, QObject *parent)
    : QIODevice(parent)
    , m_Controller(Controller)
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
    return m_Controller ? m_Controller->OnRead(data, maxlen) : 0;
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
