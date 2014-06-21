#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QScopeWidget;
class CSynth8Controller;
class CMidiInput;
class IMidiInputHandler;
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


    CSynth8Controller*  m_Controller;
    IMidiInputHandler*  m_MidiInputHandler;
    CMidiInput*         m_MidiInput;
    QScopeWidget*       m_ScopeWidget;
    CCommandStackController* m_CommandStackController;
};

#endif // MAINWINDOW_H
