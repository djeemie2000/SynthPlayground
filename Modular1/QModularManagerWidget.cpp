#include "QModularManagerWidget.h"
#include "ui_QModularManagerWidget.h"
#include <QFileDialog>
#include "Modular1Controller.h"

QModularManagerWidget::QModularManagerWidget(std::weak_ptr<CModular1Controller> Controller,
                                             QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::QModularManagerWidget)
     , m_Controller(Controller)
{
    ui->setupUi(this);

    ui->listWidget_ModuleTypes->clear();
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        for(auto& Name : Controller->GetSupportedTypes())
        {
            ui->listWidget_ModuleTypes->addItem(QString::fromStdString(Name));
        }
    }
}

QModularManagerWidget::~QModularManagerWidget()
{
    m_Controller.reset();
    delete ui;
}

void QModularManagerWidget::on_pushButton_Create_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        QList<QListWidgetItem*> Selected = ui->listWidget_ModuleTypes->selectedItems();
        QListWidgetItem* Item = 0;
        foreach(Item , Selected)
        {
            Controller->Create(Item->text().toStdString(), "");
        }
    }
    UpdateNames();
}

void QModularManagerWidget::on_pushButton_Remove_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        QList<QListWidgetItem*> Selected = ui->listWidget_ModuleNames->selectedItems();
        QListWidgetItem* Item = 0;
        foreach(Item , Selected)
        {
            Controller->Remove(Item->text().toStdString());
        }
    }
    UpdateNames();
}

void QModularManagerWidget::on_pushButton_Capture_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        Controller->Capture();
    }
}

void QModularManagerWidget::on_pushButton_Restore_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        Controller->Restore();
    }
    UpdateNames();
}

void QModularManagerWidget::UpdateNames()
{
    ui->listWidget_ModuleNames->clear();
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        for(auto& Name : Controller->GetNames())
        {
            ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
        }
    }
}

void QModularManagerWidget::on_pushButton_RemoveAll_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        Controller->RemoveAll();
    }
    UpdateNames();
}

void QModularManagerWidget::on_pushButton_Default_clicked()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        Controller->Default();
    }
}

void QModularManagerWidget::on_pushButton_Save_clicked()
{
    QString Path = QFileDialog::getSaveFileName(this, "Save Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
        {
            Controller->Save(Path.toStdString());
        }
    }
}

void QModularManagerWidget::on_pushButton_Load_clicked()
{
    QString Path = QFileDialog::getOpenFileName(this, "Load Patch", "", "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
        {
            Controller->Load(Path.toStdString());
        }
        UpdateNames();
    }
}
