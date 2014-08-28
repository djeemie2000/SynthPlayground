#include "QModularManagerWidget.h"
#include "ui_QModularManagerWidget.h"
#include "ModuleManager.h"
#include "ModuleGuiFactory.h"

QModularManagerWidget::QModularManagerWidget(std::weak_ptr<CModuleManager> Manager,
                                             QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::QModularManagerWidget)
     , m_Manager(Manager)
{
    ui->setupUi(this);

    ui->listWidget_ModuleTypes->clear();
    if(std::shared_ptr<CModuleManager> Manager = m_Manager.lock())
    {
        for(auto& Name : Manager->GetSupportedTypes())
        {
            ui->listWidget_ModuleTypes->addItem(QString::fromStdString(Name));
        }
    }
}

QModularManagerWidget::~QModularManagerWidget()
{
    m_Manager.reset();
    delete ui;
}

void QModularManagerWidget::on_pushButton_Create_clicked()
{
    if(std::shared_ptr<CModuleManager> Manager = m_Manager.lock())
    {
        QList<QListWidgetItem*> Selected = ui->listWidget_ModuleTypes->selectedItems();
        QListWidgetItem* Item = 0;
        foreach(Item , Selected)
        {
            Manager->Create(Item->text().toStdString(), "");
        }
        //update names
        ui->listWidget_ModuleNames->clear();
        for(auto& Name : Manager->GetNames())
        {
            ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
        }
    }
}

void QModularManagerWidget::on_pushButton_Remove_clicked()
{
    if(std::shared_ptr<CModuleManager> Manager = m_Manager.lock())
    {
        QList<QListWidgetItem*> Selected = ui->listWidget_ModuleNames->selectedItems();
        QListWidgetItem* Item = 0;
        foreach(Item , Selected)
        {
            Manager->Remove(Item->text().toStdString());
        }
        //update names
        ui->listWidget_ModuleNames->clear();
        for(auto& Name : Manager->GetNames())
        {
            ui->listWidget_ModuleNames->addItem(QString::fromStdString(Name));
        }
    }
}
