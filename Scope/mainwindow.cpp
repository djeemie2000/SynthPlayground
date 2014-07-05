#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QScopeWidget2.h"
#include "QScope.h"
#include "ScopeController.h"
#include "JackIOManager.h"
#include "periodicsamplegrabberproxy.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_JackIOManager()
  , m_SampleGrabber()
  , m_Controller()
  , m_ScopeWidget(0)
{
    ui->setupUi(this);

    m_JackIOManager.reset(new CJackIOManager());
    m_JackIOManager->OpenClient("Scope");

    // create IPeriodicSampleGrabber proxy
    std::shared_ptr<CPeriodicSampleGrabberProxy> GrabberProxy(new CPeriodicSampleGrabberProxy());
    m_SampleGrabber = GrabberProxy;

    m_ScopeWidget = new QScopeWidget2(*m_SampleGrabber, this);
    ui->groupBox_Scope->layout()->addWidget(m_ScopeWidget);

    QFloatScope* Scope = new QFloatScope(this);
    connect(Scope, SIGNAL(SignalSample(QVector<float>)), m_ScopeWidget, SLOT(OnSample(QVector<float>)));

    m_Controller.reset(new CScopeController(*Scope));
    GrabberProxy->Reset(m_Controller);

    m_JackIOManager->OpenAudioInput("In", m_Controller);
    m_JackIOManager->ActivateClient();
}

MainWindow::~MainWindow()
{
    m_JackIOManager->CloseClient();

    delete ui;
    delete m_ScopeWidget;
}
