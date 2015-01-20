#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"
#include "ModuleGuiParameterVisitor.h"
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>

QGenericModuleWidget::QGenericModuleWidget(std::weak_ptr<IModularModule> Module,
                                           std::weak_ptr<CJackConnectionManager> ConnectionManager,
                                           CCommandStackController &CommandStackController,
                                           QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QGenericModuleWidget)
    , m_Module(Module)
    , m_ConnectionManager(ConnectionManager)
{
    ui->setupUi(this);

    AddParameters(CommandStackController);
    AddOutputs();

    ui->groupBox_Outputs->setHidden(true);
}

QGenericModuleWidget::~QGenericModuleWidget()
{
    delete ui;
}

QGroupBox *QGenericModuleWidget::GetParametersGroupBox()
{
    return ui->groupBox_Parameters;
}

void QGenericModuleWidget::AddParameters(CCommandStackController& CommandStackController)
{
    if(std::shared_ptr<IModularModule> SPModule = m_Module.lock())
    {
        setWindowTitle(QString::fromStdString(SPModule->GetName()));
        ui->groupBox_Parameters->setTitle(QString::fromStdString(SPModule->GetName()));

        // module accepts parameter visitor around our parameters groupbox
        CGuiModuleParameterVisitor ParameterVisitor(ui->groupBox_Parameters, this, CommandStackController);
        SPModule->Accept(ParameterVisitor);
    }
}

void QGenericModuleWidget::AddOutputs()
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
            OutputsLayout->addWidget(new QLabel("-", this), Row, 1);
            ++Row;
        }
    }
}

void QGenericModuleWidget::on_checkBox_Outputs_clicked(bool checked)
{
    ui->groupBox_Outputs->setHidden(!checked);
}
