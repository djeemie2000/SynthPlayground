#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QLedWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setText("C: 073");


    QStatusLedWidget* Led1 = new QStatusLedWidget(this);
    ui->centralWidget->layout()->addWidget(Led1);
    connect(ui->pushButton, SIGNAL(clicked(bool)), Led1, SLOT(OnStatus(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

