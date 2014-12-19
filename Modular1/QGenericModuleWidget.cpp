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
