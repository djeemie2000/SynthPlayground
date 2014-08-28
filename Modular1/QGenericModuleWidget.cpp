#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"

QGenericModuleWidget::QGenericModuleWidget(IModularModule &Module, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGenericModuleWidget)
{
    ui->setupUi(this);

    ui->groupBox_Ins->setLayout(new QVBoxLayout(this));
    ui->groupBox_Outs->setLayout(new QVBoxLayout(this));

    setWindowTitle(QString::fromStdString(Module.GetName()));

    for(auto& Name : Module.GetInputNames())
    {
        AddInput(QString::fromStdString(Name));
    }
    for(auto& Name : Module.GetOutputNames())
    {
        AddOutput(QString::fromStdString(Name));
    }
    for(auto& Name : Module.GetMidiInputNames())
    {
        AddInput(QString::fromStdString(Name));
    }

}

QGenericModuleWidget::~QGenericModuleWidget()
{
    delete ui;
}

void QGenericModuleWidget::AddInput(QString Name)
{
    ui->groupBox_Ins->layout()->addWidget(new QLabel(Name, this));
}

void QGenericModuleWidget::AddOutput(QString Name)
{
    ui->groupBox_Outs->layout()->addWidget(new QLabel(Name, this));
}
