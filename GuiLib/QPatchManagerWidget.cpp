#include "QPatchManagerWidget.h"
#include "ui_QPatchManagerWidget.h"
#include <QFileDialog>
#include "CommandStackController.h"

QPatchManagerWidget::QPatchManagerWidget(CCommandStackController& Controller, QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::QPatchManagerWidget)
  , m_Controller(Controller)
{
    ui->setupUi(this);
}

QPatchManagerWidget::~QPatchManagerWidget()
{
    delete ui;
}

void QPatchManagerWidget::on_pushButton_Load_clicked()
{
    QString Path = QFileDialog::getOpenFileName(this, "Load Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        //m_Importer->Default();
        m_Controller.Import(Path.toStdString());
    }
}

void QPatchManagerWidget::on_pushButton_Save_clicked()
{
    QString Path = QFileDialog::getSaveFileName(this, "Save Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        m_Controller.Export(Path.toStdString());
    }
}

void QPatchManagerWidget::on_pushButton_Default_clicked()
{
    m_Controller.Default();
}
