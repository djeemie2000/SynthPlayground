#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GuiItems.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include "QPatchManagerWidget.h"
#include "GuiCommandStack.h"
#include "ModuleManager.h"
#include "ModuleFactory.h"
#include "ModularFactoryWidget.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_CommandStackController()
  , m_ModuleManager()
{
    ui->setupUi(this);

    m_CommandStackController.reset(new CCommandStackController());
    std::shared_ptr<IModuleFactory> Factory(new CModuleFactory(m_CommandStackController));
    m_ModuleManager.reset(new CModuleManager(Factory));

    // build gui
    ui->centralWidget->layout()->addWidget(new QPatchManagerWidget(*m_CommandStackController, this));
    ui->centralWidget->layout()->addWidget(new QModularFactoryWidget(m_ModuleManager, this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

