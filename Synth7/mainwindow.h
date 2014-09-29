#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class QScopeWidget;
class CSynth7Controller;
class CAlsaMidiInput;
class IMidiHandler;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CSynth7Controller>  m_Controller;
    std::shared_ptr<IMidiHandler>  m_MidiInputHandler;
    std::shared_ptr<CAlsaMidiInput>         m_MidiInput;
    QScopeWidget*       m_ScopeWidget;
};

#endif // MAINWINDOW_H
