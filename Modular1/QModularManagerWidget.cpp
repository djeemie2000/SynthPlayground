#include "QModularManagerWidget.h"
#include "ui_QModularManagerWidget.h"
#include <QFileDialog>
#include "Modular1Controller.h"

QModularManagerWidget::QModularManagerWidget(std::weak_ptr<CModular1Controller> Controller,
                                             QWidget *parent)
     : QWidget(parent)
     , ui(new Ui::QModularManagerWidget)
     , m_Controller(Controller)
     , m_Path()
{
    ui->setupUi(this);

    ui->toolBox_Modules->removeItem(1);
    ui->toolBox_Modules->removeItem(0);

    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        for(auto& Category : Controller->GetSupportedCategories())
        {
            QListWidget* ListWidget = new QListWidget(this);
            for(auto& Type : Controller->GetSupportedTypes(Category))
            {
                ListWidget->addItem(QString::fromStdString(Type));
            }
            ui->toolBox_Modules->addItem(ListWidget, QString::fromStdString(Category));
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
        QListWidget* ListWidget = dynamic_cast<QListWidget*>(ui->toolBox_Modules->currentWidget());
        QList<QListWidgetItem*> Selected = ListWidget->selectedItems();//ui->listWidget_ModuleTypes->selectedItems();
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
    QString Path = QFileDialog::getSaveFileName(this, "Save Patch", m_Path, "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
        {
            Controller->Save(Path.toStdString());
        }
        m_Path = Path;
    }
}

void QModularManagerWidget::on_pushButton_Load_clicked()
{
    QString Path = QFileDialog::getOpenFileName(this, "Load Patch", m_Path, "Patch (*.xml);;All Files (*)");
    if(!Path.isEmpty())
    {
        if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
        {
            Controller->Load(Path.toStdString());
        }
        m_Path = Path;
        UpdateNames();
    }
}

void QModularManagerWidget::on_listWidget_ModuleNames_itemSelectionChanged()
{
    if(std::shared_ptr<CModular1Controller> Controller = m_Controller.lock())
    {
        std::string Name = ui->listWidget_ModuleNames->currentItem()->text().toStdString();
        Controller->Show(Name);
    }
}

