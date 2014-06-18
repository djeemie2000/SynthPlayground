#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "CommandStackController.h"
#include "AppSpecific.h"
#include "QCommandSender.h"
#include "QCommandStackHandler.h"


void ConnectCheckableToolButton(QToolButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalBoolValueChanged(bool)), Button, SLOT(setChecked(bool)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectSpinbox(QSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(int)), Sender, SLOT(OnIntChanged(int)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalIntValueChanged(int)), SpinBox, SLOT(setValue(int)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectDoubleSpinbox(QDoubleSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(double)), Sender, SLOT(OnDoubleChanged(double)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalDoubleValueChanged(double)), SpinBox, SLOT(setValue(double)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectCombobox(QComboBox* ComboBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(ComboBox, SIGNAL(currentIndexChanged(int)), Sender, SLOT(OnIntChanged(int)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalIntValueChanged(int)), ComboBox, SLOT(setCurrentIndex(int)));
    Controller.Register(ParameterName, SPCommandStackHandler(Reciever));
}

void ConnectPushButton(QPushButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller)
{
    // not checkable push button!
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Controller, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // need to get feedback from controller ???
}

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_Controller()
  , m_CommandController()
{
    ui->setupUi(this);
    ui->comboBox_Param4->addItem("Select0");
    ui->comboBox_Param4->addItem("Select1");
    ui->comboBox_Param4->addItem("Select2");
    ui->comboBox_Param4->addItem("Select3");
    ui->comboBox_Param4->setCurrentIndex(0);

    // app-specific controller
    m_Controller.reset(new CAppSpecificController());

    m_CommandController.reset(new CCommandStackController(BuildAppSpecificCmdFunctionMap(*m_Controller), BuildAppSpecificDefaults()));

    // construct gui:

    // tool button, param1
    ConnectCheckableToolButton(ui->toolButton_Param1, this, "Internal/Param1", *m_CommandController);

    // spinbox, param2
    ConnectSpinbox(ui->spinBox_Param2, this, "Internal/Param2", *m_CommandController);

    // double spin box, param3
    ConnectDoubleSpinbox(ui->doubleSpinBox_Param3, this, "Internal/Param3", *m_CommandController);

    // combo box, param4
    ConnectCombobox(ui->comboBox_Param4, this, "Internal/Param4", *m_CommandController);

    // push button, param5
    ConnectPushButton(ui->pushButton_Param5, this, "Internal/Param5", *m_CommandController);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Export_clicked()
{
    QString Path = QFileDialog::getSaveFileName(this, "Save Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        m_CommandController->Export(Path.toStdString());
    }
}

void MainWindow::on_pushButton_Test_clicked()
{
    // toggle button!
    ui->toolButton_Param1->setDown(!ui->toolButton_Param1->isDown());
    ui->spinBox_Param2->setValue(ui->spinBox_Param2->value()+1);
    ui->doubleSpinBox_Param3->setValue(ui->doubleSpinBox_Param3->value()+0.01);
    ui->comboBox_Param4->setCurrentIndex((ui->comboBox_Param4->currentIndex()+1)%ui->comboBox_Param4->count());
    ui->pushButton_Param5->click();
}

void MainWindow::on_pushButton_Import_clicked()
{
    QString Path = QFileDialog::getOpenFileName(this, "Load Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        //m_Importer->Default();
        m_CommandController->Import(Path.toStdString());
    }
}

void MainWindow::on_pushButton_Default_clicked()
{
    m_CommandController->Default();
}
