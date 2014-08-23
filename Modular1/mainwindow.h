#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

namespace Ui {
class MainWindow;
}

class CCommandStackController;
class CModuleManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CCommandStackController> m_CommandStackController;
    std::shared_ptr<CModuleManager> m_ModuleManager;
};

#endif // MAINWINDOW_H
