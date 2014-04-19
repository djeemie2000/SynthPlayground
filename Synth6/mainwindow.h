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


    void on_spinBox_BitCrushserDepth_valueChanged(int arg1);
    void on_spinBox_SnHPeriod_valueChanged(int arg1);
    void on_spinBox_RipplerThreshold_valueChanged(int arg1);
    void on_spinBox_RipplerStrength_valueChanged(int arg1);

    void on_comboBox_Combinor_activated(const QString &arg1);
    void on_doubleSpinBox_1_Amplitude_valueChanged(double arg1);
    void on_doubleSpinBox_2_Amplitude_valueChanged(double arg1);
    void on_comboBox_1_Operator_activated(const QString &arg1);
    void on_comboBox_2_Operator_activated(const QString &arg1);
    void on_doubleSpinBox_1_Frequency_valueChanged(double arg1);
    void on_doubleSpinBox_2_Frequency_valueChanged(double arg1);
    void on_doubleSpinBox_1_PhaseShift_valueChanged(double arg1);
    void on_doubleSpinBox_2_PhaseShift_valueChanged(double arg1);

    void on_pushButton_DetuneSync_clicked();

private:
    void CreateAudioOutput();

    Ui::MainWindow *ui;

    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;
    bool        m_ScopeAutoGrab;

    CController* m_Controller;
};

#endif // MAINWINDOW_H
