#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"

QGenericModuleWidget::QGenericModuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGenericModuleWidget)
{
    ui->setupUi(this);
}

QGenericModuleWidget::~QGenericModuleWidget()
{
    delete ui;
}
