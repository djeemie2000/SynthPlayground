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
class CController;
class CStepSequencer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    CController* m_Controller;
};

#endif // MAINWINDOW_H
