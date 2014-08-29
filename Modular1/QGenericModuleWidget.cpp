#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"
#include "ModuleGuiParameterVisitor.h"

QGenericModuleWidget::QGenericModuleWidget(IModularModule &Module, CCommandStackController &CommandStackController, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGenericModuleWidget)
{
    ui->setupUi(this);

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

    // module accepts parameter visitor around our parameters groupbox
    CModuleGuiParameterVisitor ParameterVisitor(ui->groupBox_Parameters, this, CommandStackController);
    Module.Accept(ParameterVisitor);
}

QGenericModuleWidget::~QGenericModuleWidget()
{
    delete ui;
}

QGroupBox *QGenericModuleWidget::GetParametersGroupBox()
{
    return ui->groupBox_Parameters;
}

void QGenericModuleWidget::AddInput(QString Name)
{
    ui->groupBox_Ins->layout()->addWidget(new QLabel(Name, this));
}

void QGenericModuleWidget::AddOutput(QString Name)
{
    ui->groupBox_Outs->layout()->addWidget(new QLabel(Name, this));
}
