#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "CommandStackController.h"
#include "AppSpecific.h"
#include "QCommandSender.h"
#include "QCommandStackHandler.h"


void ConnectToolButton(QToolButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Handler, CCommandStackController& FeedbackDistributor)
{
    // gui -> controller
    QCommandSender* Sender = new QCommandSender(ParameterName, Handler, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), Sender, SLOT(OnBoolChanged(bool)));
    // controller -> gui
    QCommandStackHandler* Reciever = new QCommandStackHandler();//no ownership by parent!
    Parent->connect(Reciever, SIGNAL(SignalBoolValueChanged(bool)), Button, SLOT(setChecked(bool)));
    FeedbackDistributor.Register(ParameterName, SPCommandStackHandler(Reciever));
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
    ConnectToolButton(ui->toolButton_Param1, this, "Internal/Param1", *m_CommandController, *m_CommandController);

    // spinbox, param2
    QCommandSender* SenderParam2 = new QCommandSender("Internal/Param2", *m_CommandController, this);
    connect(ui->spinBox_Param2, SIGNAL(valueChanged(int)), SenderParam2, SLOT(OnIntChanged(int)));

    QCommandStackHandler* RecieverParam2 = new QCommandStackHandler();//no ownership by parent!
    connect(RecieverParam2, SIGNAL(SignalIntValueChanged(int)), ui->spinBox_Param2, SLOT(setValue(int)));
    m_CommandController->Register("Internal/Param2", SPCommandStackHandler(RecieverParam2));

    // double spin box, param2
    QCommandSender* SenderParam3 = new QCommandSender("Internal/Param3", *m_CommandController, this);
    connect(ui->doubleSpinBox_Param3, SIGNAL(valueChanged(double)), SenderParam3, SLOT(OnDoubleChanged(double)));

    QCommandStackHandler* RecieverParam3 = new QCommandStackHandler();//no ownership by parent!
    connect(RecieverParam3, SIGNAL(SignalDoubleValueChanged(double)), ui->doubleSpinBox_Param3, SLOT(setValue(double)));
    m_CommandController->Register("Internal/Param3", SPCommandStackHandler(RecieverParam3));

    // combo box, param4
    QCommandSender* SenderParam4 = new QCommandSender("Internal/Param4", *m_CommandController, this);
    connect(ui->comboBox_Param4, SIGNAL(currentIndexChanged(int)), SenderParam4, SLOT(OnIntChanged(int)));

    QCommandStackHandler* RecieverParam4 = new QCommandStackHandler();//no ownership by parent!
    connect(RecieverParam4, SIGNAL(SignalIntValueChanged(int)), ui->comboBox_Param4, SLOT(setCurrentIndex(int)));
    m_CommandController->Register("Internal/Param4", SPCommandStackHandler(RecieverParam4));

    // push button, param5
    QCommandSender* SenderParam5 = new QCommandSender("Internal/Param5", *m_CommandController, this);
    connect(ui->pushButton_Param5, SIGNAL(clicked()), SenderParam5, SLOT(OnChanged()));
    // need feedback??
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
