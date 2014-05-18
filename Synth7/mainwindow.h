#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <cstdint>
#include <QMainWindow>
#include <QAudio>
#include <QVector>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class QAudioOutput;
class QAudioIODevice;
class QPushButton;
class QSpinBox;
class QComboBox;
class QToolButton;
class CController;
class CStepSequencer;

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
    void OnSample(QVector<std::int16_t> Sample);

    void on_pushButton_ZoomInHorizontal_clicked();
    void on_pushButton_ZoomOutHorizontal_clicked();
    void on_pushButton_ScopeGrab_clicked();
    void on_checkBox_ScopeGrabRepeated_clicked(bool checked);

private:
    void CreateAudioOutput();

    Ui::MainWindow *ui;

    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;
    bool        m_ScopeAutoGrab;
    QVector<QToolButton*> m_StepSequencerActiveBtn;
    QVector<QComboBox*> m_StepSequencerNoteBox;
    QVector<QSpinBox*> m_StepSequencerOctaveBox;

    CController* m_Controller;
};

#endif // MAINWINDOW_H
