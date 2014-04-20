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

    void on_doubleSpinBox_SmootherFactor_valueChanged(double arg1);

    void on_spinBox_BitCrushserDepth_valueChanged(int arg1);
    void on_spinBox_SnHPeriod_valueChanged(int arg1);
    void on_spinBox_RipplerThreshold_valueChanged(int arg1);
    void on_spinBox_RipplerStrength_valueChanged(int arg1);

    void on_comboBox_WaveForm2_activated(const QString &arg1);
    void on_doubleSpinBox_MorpherMin_valueChanged(double arg1);
    void on_doubleSpinBox_MorpherMax_valueChanged(double arg1);
    void on_doubleSpinBox_MorphFrequency_valueChanged(double arg1);
    void on_pushButton_MorpherSync_clicked();

private:
    void CreateAudioOutput();

    Ui::MainWindow *ui;

    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;
    bool        m_ScopeAutoGrab;

    std::unique_ptr<CController> m_Controller;
};

#endif // MAINWINDOW_H