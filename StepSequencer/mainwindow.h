#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class CStepSequencerController;
class CJackIOManager;
class CCommandStackController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CJackIOManager>   m_AudioOutput;
    std::shared_ptr<CStepSequencerController>  m_Controller;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
};

#endif // MAINWINDOW_H
