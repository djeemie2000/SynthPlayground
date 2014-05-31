#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QScopeWidget;
class CSynth7Controller;
class CMidiInput;
class IMidiInputHandler;

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
    IMidiInputHandler*  m_MidiInputHandler;
    CMidiInput*         m_MidiInput;
    QScopeWidget*       m_ScopeWidget;
};

#endif // MAINWINDOW_H
