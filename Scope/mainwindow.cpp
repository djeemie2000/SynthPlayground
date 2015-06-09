#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphWidget.h"
#include "QGraphBufferHandler.h"
#include "CommandStackController.h"
#include "ScopeModule.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_CommandStackController()
  , m_ScopeModule()
{
    ui->setupUi(this);

    QGraphWidget* GraphWidget = new QGraphWidget(this);
    ui->groupBox_Scope->layout()->addWidget(GraphWidget);

    QGraphBufferHandler* BufferHandler = new QGraphBufferHandler();
    connect(BufferHandler, SIGNAL(SignalGraph(QVector<QPointF>)), GraphWidget, SLOT(setGraph(QVector<QPointF>)));

    m_CommandStackController.reset(new CCommandStackController());
    m_ScopeModule.reset(new CScopeModule("Scope", *m_CommandStackController, std::shared_ptr<IBufferHandler<float>>(BufferHandler)));
}

MainWindow::~MainWindow()
{
    m_ScopeModule.reset();
    m_CommandStackController.reset();

    delete ui;
}
