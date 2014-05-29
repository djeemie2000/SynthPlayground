#ifndef QAUDIODEVICEWIDGET_H
#define QAUDIODEVICEWIDGET_H

#include <QWidget>
#include <QAudio>

namespace Ui {
class QAudioDeviceWidget;
}

class QAudioOutput;
class QAudioIODevice;
class IAudioSource;

class QAudioDeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QAudioDeviceWidget(IAudioSource& AudioSource, int SamplingFrequency, QWidget *parent = 0);
    ~QAudioDeviceWidget();

private slots:
    void on_pushButton_Play_clicked(bool checked);
    void on_horizontalSlider_Volume_sliderMoved(int position);
    void on_comboBox_AudioDevice_currentIndexChanged(const QString &);

    void notified();
    void handleStateChanged(QAudio::State state);

private:
    void CreateAudioOutput();

    Ui::QAudioDeviceWidget *ui;

    IAudioSource& m_AudioSource;
    int m_SamplingFrequency;
    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;

};

#endif // QAUDIODEVICEWIDGET_H
