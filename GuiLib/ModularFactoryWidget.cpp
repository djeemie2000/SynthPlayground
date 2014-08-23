#include "ModularFactoryWidget.h"
#include "ui_ModularFactoryWidget.h"
#include "ModuleManager.h"

QModularFactoryWidget::QModularFactoryWidget(std::shared_ptr<CModuleManager> Manager, QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::QModularFactoryWidget)
     , m_Manager(Manager)
{
    ui->setupUi(this);

    ui->listWidget_ModuleTypes->clear();
    for(auto& Name : m_Manager->GetSupportedTypes())
    {
        ui->listWidget_ModuleTypes->addItem(QString::fromStdString(Name));
    }
}

QModularFactoryWidget::~QModularFactoryWidget()
{
    delete ui;
}

void QModularFactoryWidget::on_pushButton_Create_clicked()
{
    QList<QListWidgetItem*> Selected = ui->listWidget_ModuleTypes->selectedItems();
    if(!Selected.empty())
    {
        m_Manager->Create(Selected.at(0)->text().toStdString(), "");
    }
    //update names
    ui->listWidget_ModuleNames->clear();
    for(auto& Name : m_Manager->GetNames())
    {
        ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
    }
}

void QModularFactoryWidget::on_pushButton_Remove_clicked()
{
    QList<QListWidgetItem*> Selected = ui->listWidget_ModuleNames->selectedItems();
    if(!Selected.empty())
    {
        m_Manager->Remove(Selected.at(0)->text().toStdString());
    }
    //update names
    ui->listWidget_ModuleNames->clear();
    for(auto& Name : m_Manager->GetNames())
    {
        ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
    }
}
