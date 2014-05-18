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
    void on_comboBox_AudioDevice_activated(int);

    void notified();
    void handleStateChanged(QAudio::State state);

private:
    void CreateAudioOutput();

    Ui::MainWindow *ui;

    QAudioOutput* m_AudioOutput;
    QAudioIODevice* m_AudioIODevice;

    CController* m_Controller;
};

#endif // MAINWINDOW_H
