#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class QKeyboardWidget;
class IPeriodicSampleGrabber;
class CKeyboardController;
class CJackIOManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CJackIOManager>   m_JackIOManager;
    std::shared_ptr<CKeyboardController>  m_Controller;
    QKeyboardWidget*                m_KeyboardWidget;
};

#endif // MAINWINDOW_H
