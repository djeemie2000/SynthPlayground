#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <cstdint>
#include <QMainWindow>
#include <QAudio>

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
class CSynth7Controller;
class CMidiInput;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    CSynth7Controller*  m_Controller;
    CMidiInput*         m_MidiInput;
};

#endif // MAINWINDOW_H
