#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GuiItems.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"
#include <QDockWidget>
#include "GuiCommandStack.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "QModularManagerWidget.h"
#include "ModuleGuiFactory.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_CommandStackController()
  , m_ModuleManager()
{
    ui->setupUi(this);

    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    std::shared_ptr<CModuleGuiFactory> GuiFactory(new CModuleGuiFactory(Factory, this));
    m_ModuleManager.reset(new CModuleManager(GuiFactory));

    // build gui
    QDockWidget* Patch = new QDockWidget(this);
    Patch->setFeatures(QDockWidget::DockWidgetMovable);
    Patch->setWidget(new QPatchManagerWidget(*m_CommandStackController, this));
    addDockWidget(Qt::RightDockWidgetArea, Patch);


    QModularManagerWidget* FactoryWidget = new QModularManagerWidget(m_ModuleManager, this);
    connect(FactoryWidget, SIGNAL(SignalRemoved(QString)), this, SLOT(OnRemovedModule(QString)));

    QDockWidget* Fact = new QDockWidget(this);
    Fact->setFeatures(QDockWidget::DockWidgetMovable);
    Fact->setWidget(FactoryWidget);
    addDockWidget(Qt::RightDockWidgetArea, Fact);

    //ui->centralWidget->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));
    //ui->centralWidget->layout()->addWidget(new QModularFactoryWidget(m_ModuleManager, this));
}

MainWindow::~MainWindow()
{
    m_ModuleManager.reset();
    delete ui;
}

