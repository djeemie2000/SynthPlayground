#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class CEffectsAppController;
class CJackIOManager;
class CAlsaMidiInput;
class CMidiInputController;
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
    std::shared_ptr<CEffectsAppController>  m_Controller;
    std::shared_ptr<CMidiInputController>  m_MidiInputController;
    std::shared_ptr<CAlsaMidiInput>         m_MidiInput;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
};

#endif // MAINWINDOW_H
