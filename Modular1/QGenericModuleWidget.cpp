#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"
#include "ModuleGuiParameterVisitor.h"
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>

QGenericModuleWidget::QGenericModuleWidget(std::weak_ptr<IModularModule> Module,
                                           CCommandStackController &CommandStackController,
                                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QGenericModuleWidget)
    , m_Module(Module)
{
    ui->setupUi(this);

    if(std::shared_ptr<IModularModule> SPModule = m_Module.lock())
    {
        setWindowTitle(QString::fromStdString(SPModule->GetName()));
        ui->groupBox_Parameters->setTitle(QString::fromStdString(SPModule->GetName()));

        // module accepts parameter visitor around our parameters groupbox
        CGuiModuleParameterVisitor ParameterVisitor(ui->groupBox_Parameters, this, CommandStackController);
        SPModule->Accept(ParameterVisitor);
    }

    // list outputs
    OnUpdateConnections();
}

QGenericModuleWidget::~QGenericModuleWidget()
{
    delete ui;
}

QGroupBox *QGenericModuleWidget::GetParametersGroupBox()
{
    return ui->groupBox_Parameters;
}

void QGenericModuleWidget::OnUpdateConnections()
{
    if(std::shared_ptr<IModularModule> SPModule = m_Module.lock())
    {
        // list outputs
        QGridLayout* OutputsLayout = new QGridLayout();
        ui->groupBox_Outputs->setLayout(OutputsLayout);
        int Row = 0;
        for(auto& OutputName : SPModule->GetOutputNames())
        {
            OutputsLayout->addWidget(new QLabel(QString::fromStdString(OutputName), this), Row, 0);
            OutputsLayout->addWidget(new QLabel("TBD:TBD", this), Row, 1);
            ++Row;
        }
    }
}

void QGenericModuleWidget::on_checkBox_Outputs_clicked(bool checked)
{
    ui->groupBox_Outputs->setHidden(!checked);
}
