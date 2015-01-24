#include "QGenericModuleWidget.h"
#include "ui_QGenericModuleWidget.h"
#include "ModularModuleI.h"
#include "ModuleGuiParameterVisitor.h"
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include "JackConnectionManager.h"
#include "QConnectionChangedListener.h"

#include <iostream>

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
    AddConnectionListener();

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

void QGenericModuleWidget::OnConnectionChanged(QString OutputPortName, QString InputPortName, bool Connect)
{
    // check if output is of our module
    // if so,
    //      update connected inputs
    // TODO handle multiple connected outputs
    if(std::shared_ptr<IModularModule> SPModule = m_Module.lock())
    {
        std::string OutModuleName = PortNameToClientName(OutputPortName.toStdString());
        if(OutModuleName==SPModule->GetName())
        {
            std::string OutputName = PortNameToInOutName(OutputPortName.toStdString());

            // debug:
            std::cout << SPModule->GetName() << " : " << (Connect?"Connecting":"Disconnecting") << OutputName<< " -> " << InputPortName.toStdString() << std::endl;

            if(QLabel* Label = m_OutputConnectionLabel[OutputName])
            {
                if(Connect)
                {
                    Label->setText(InputPortName);
                }
                else
                {
                    Label->setText("-");
                }
            }
        }
    }
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
            QLabel* Label = new QLabel("-", this);
            m_OutputConnectionLabel[OutputName] = Label;
            OutputsLayout->addWidget(Label, Row, 1);
            ++Row;
        }
    }
}

void QGenericModuleWidget::AddConnectionListener()
{
    if(std::shared_ptr<CJackConnectionManager> ConnectionManager = m_ConnectionManager.lock())
    {
        QConnectionChangedListener* Listener = new QConnectionChangedListener();
        connect(Listener, SIGNAL(SignalConnectionChanged(QString,QString,bool)), this, SLOT(OnConnectionChanged(QString,QString,bool)));
        ConnectionManager->Register(std::shared_ptr<IConnectionChangedListener>(Listener));
    }
}

void QGenericModuleWidget::on_checkBox_Outputs_clicked(bool checked)
{
    ui->groupBox_Outputs->setHidden(!checked);
}
