#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"
#include "ModuleGuiParameterVisitor.h"
#include <QLabel>

QGenericModuleWidget::QGenericModuleWidget(IModularModule &Module, CCommandStackController &CommandStackController, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGenericModuleWidget)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromStdString(Module.GetName()));

    AddInputs(Module);
    AddOutputs(Module);

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

void QGenericModuleWidget::AddInputs(IModularModule &Module)
{
    QGridLayout* InputLayout = new QGridLayout(this);
    ui->groupBox_Ins->setLayout(InputLayout);
    int idxInput = 0;
    for(auto& Name : Module.GetInputNames())
    {
        InputLayout->addWidget(new QLabel(QString::fromStdString(Name), this), idxInput++, 0);
    }
    for(auto& Name : Module.GetMidiInputNames())
    {
        InputLayout->addWidget(new QLabel(QString::fromStdString(Name), this), idxInput++, 0);
    }
}

void QGenericModuleWidget::AddOutputs(IModularModule &Module)
{
    QGridLayout* OutputLayout = new QGridLayout(this);
    ui->groupBox_Outs->setLayout(OutputLayout);
    int idxOutput = 0;
    for(auto& Name : Module.GetOutputNames())
    {
        OutputLayout->addWidget(new QLabel(QString::fromStdString(Name), this), idxOutput++, 0);
    }
}
