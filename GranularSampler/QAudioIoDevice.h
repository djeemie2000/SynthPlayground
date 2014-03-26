#ifndef QAUDIOIODEVICE_H
#define QAUDIOIODEVICE_H

#include <QIODevice>

class CGranularSamplerController;

class QAudioIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit QAudioIODevice(CGranularSamplerController* Controller, QObject *parent = 0);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);
    qint64 bytesAvailable() const;

private:
    CGranularSamplerController* m_Controller;
};

#endif // QAUDIOIODEVICE_H
