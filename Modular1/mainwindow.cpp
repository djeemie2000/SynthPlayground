#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GuiItems.h"
#include "CommandStackController.h"
#include "CommandStack.h"
#include <QDockWidget>
#include "GuiCommandStack.h"
#include "QModularManagerWidget.h"
#include "Modular1Controller.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_Controller()
{
    ui->setupUi(this);

    m_Controller.reset(new CModular1Controller(this));

    // build gui
    QModularManagerWidget* ModularManagerWidget = new QModularManagerWidget(m_Controller, this);//check destructor/use weak_ptr?

    QDockWidget* Mgr = new QDockWidget(this);
    Mgr->setFeatures(QDockWidget::DockWidgetMovable);
    Mgr->setWidget(ModularManagerWidget);
    addDockWidget(Qt::RightDockWidgetArea, Mgr);
}

MainWindow::~MainWindow()
{
    m_Controller.reset();
    delete ui;
}
