#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class QScopeWidget2;
class IPeriodicSampleGrabber;
class CScopeController;
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
    std::shared_ptr<IPeriodicSampleGrabber> m_SampleGrabber;
    std::shared_ptr<CScopeController>  m_Controller;
    QScopeWidget2*       m_ScopeWidget;
};

#endif // MAINWINDOW_H
