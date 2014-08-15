#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class CSynth12Controller;
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

    void on_toolButton_Carrier_Browse_clicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CJackIOManager>   m_AudioOutput;
    std::shared_ptr<CSynth12Controller>  m_Controller;
    std::shared_ptr<CMidiInputController>  m_MidiInputController;
    std::shared_ptr<CAlsaMidiInput>         m_MidiInput;
    std::shared_ptr<CCommandStackController> m_CommandStackController;
};

#endif // MAINWINDOW_H
