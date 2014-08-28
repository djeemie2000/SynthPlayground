#include "QModularManagerWidget.h"
#include "ui_QModularManagerWidget.h"
#include "ModuleManager.h"
#include "ModuleGuiFactory.h"

QModularManagerWidget::QModularManagerWidget(std::shared_ptr<CModuleManager> Manager,
                                             std::shared_ptr<CModuleGuiFactory> Factory,
                                             QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::QModularManagerWidget)
     , m_Manager(Manager)
     , m_Factory(Factory)
{
    ui->setupUi(this);

    ui->listWidget_ModuleTypes->clear();
    for(auto& Name : m_Manager->GetSupportedTypes())
    {
        ui->listWidget_ModuleTypes->addItem(QString::fromStdString(Name));
    }
}

QModularManagerWidget::~QModularManagerWidget()
{
    delete ui;
}

void QModularManagerWidget::on_pushButton_Create_clicked()
{
    QList<QListWidgetItem*> Selected = ui->listWidget_ModuleTypes->selectedItems();
    //if(!Selected.empty())
    QListWidgetItem* Item = 0;
    foreach(Item , Selected)
    {
        m_Manager->Create(Item->text().toStdString(), "");
    }
    //update names
    ui->listWidget_ModuleNames->clear();
    for(auto& Name : m_Manager->GetNames())
    {
        ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
    }
}

void QModularManagerWidget::on_pushButton_Remove_clicked()
{
    QList<QListWidgetItem*> Selected = ui->listWidget_ModuleNames->selectedItems();
    QListWidgetItem* Item = 0;
    foreach(Item , Selected)
    {
        m_Manager->Remove(Item->text().toStdString());
        m_Factory->Remove(Item->text().toStdString());
    }
    //update names
    ui->listWidget_ModuleNames->clear();
    for(auto& Name : m_Manager->GetNames())
    {
        ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
    }
}
