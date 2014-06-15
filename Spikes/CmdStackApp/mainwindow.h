#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ICommandStackHandler;
class IExporter;
class CAppSpecificController;
class IImporter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Export_clicked();
    void on_pushButton_Test_clicked();

    void on_pushButton_Import_clicked();

    void on_pushButton_Default_clicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<CAppSpecificController> m_Controller;
    std::shared_ptr<ICommandStackHandler> m_Handler;
    std::shared_ptr<IExporter> m_Exporter;
    std::shared_ptr<IImporter> m_Importer;
};

#endif // MAINWINDOW_H
