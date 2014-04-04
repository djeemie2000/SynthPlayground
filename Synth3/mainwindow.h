#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <inttypes.h>
#include <QMainWindow>
#include <QAudio>
#include <QVector>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class QAudioOutput;
class QAudioIODevice;
class CController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Play_clicked();
    void on_pushButton_Stop_clicked();
    void on_horizontalSlider_AudioOutputVolume_valueChanged(int value);

    void notified();
    void handleStateChanged(QAudio::State state);
    void OnTimer();

    void on_comboBox_AudioDevice_activated(int);

    void OnSampleSize(int Size);
    void OnSample(QVector<std::uint8_t> Sample);

    void on_pushButton_ZoomInHorizontal_clicked();
    void on_pushButton_ZoomOutHorizontal_clicked();
    void on_pushButton_ScopeGrab_clicked();
    void on_checkBox_ScopeGrabRepeated_clicked(bool checked);

    void on_doubleSpinBox_Frequency_valueChanged(double arg1);
    void on_comboBox_WaveForm_activated(const QString &arg1);

    void on_doubleSpinBox_ModifierFrequency_valueChanged(double arg1);
    void on_pushButton_Sync_clicked();
    void on_doubleSpinBox_SmootherFactor_valueChanged(double arg1);
    void on_doubleSpinBox_SyncPhaseShift_valueChanged(double arg1);

    void on_doubleSpinBox_WaveShaperStrength_valueChanged(double arg1);

    void on_comboBox_WaveShaper_activated(const QString &arg1);

    void on_doubleSpinBox_WaveShaperPhaseShift_valueChanged(double arg1);

private:
    void CreateAudioOutput();


    Ui::MainWindow *ui;

    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;
    bool        m_ScopeAutoGrab;

    std::unique_ptr<CController> m_Controller;
};

#endif // MAINWINDOW_H
