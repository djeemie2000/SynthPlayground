#include "QScopeWidget.h"
#include "ui_QScopeWidget.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "SampleGrabberI.h"

QScopeWidget::QScopeWidget(ISampleGrabber& Grabber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QScopeWidget)
  , m_Grabber(Grabber)
  , m_AutoGrab(true)
{
    ui->setupUi(this);

    QGraphicsScene* Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(Scene);

    Scene->setForegroundBrush(QColor(0,0,0,92));

    ui->graphicsView->show();

    // timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    timer->start(1000);
}

QScopeWidget::~QScopeWidget()
{
    delete ui;
}

void QScopeWidget::OnSample(QVector<std::int16_t> Sample)
{
    if(!Sample.empty())
    {
        if(QGraphicsScene* Scene = ui->graphicsView->scene())
        {
            // clear all previous items
            QList<QGraphicsItem*> Items = Scene->items();
            for(auto Item : Items)
            {
                Scene->removeItem(Item);
            }

            // center around 'middle' of sample
            int Offset = -Sample.size()/2;

            // show red line as x axis
            QPen Pen(Qt::red);
            Pen.setWidth(3);
            Scene->addLine(Offset, 0, Offset+Sample.size(), 0, Pen);

            // show min and max amplitude lines
            Scene->addLine(Offset, -127, Offset+Sample.size(), -127, QPen(Qt::red));
            Scene->addLine(Offset, 127, Offset+Sample.size(), 127, QPen(Qt::red));

            // show sample as path
            QPainterPath Path;
            Path.moveTo(Offset, -Sample[0]/256);
            int DeltaX = 2;
            for(int x = 0; x<Sample.size(); x+=DeltaX)
            {
                // value increases ~ y decreases!
                QPointF Pt(Offset+x, -Sample.at(x)/256);
                Path.lineTo(Pt);
            }
            Scene->addPath(Path, QPen(Qt::green));

        }
    }
}

void QScopeWidget::on_toolButton_Grab_clicked()
{
    int GrabSize = ui->spinBox_GrabSize->value();
    m_Grabber.OnGrab(GrabSize);
}

void QScopeWidget::on_toolButton_ZoomIn_clicked()
{
    ui->graphicsView->scale(1.1f, 1.1f);
}

void QScopeWidget::on_toolButton_ZoomOut_clicked()
{
    ui->graphicsView->scale(0.9f, 0.9f);
}

void QScopeWidget::on_checkBox_GrabRepeated_clicked(bool checked)
{
    m_AutoGrab = checked;
}

void QScopeWidget::OnTimer()
{
    if(m_AutoGrab)
    {
        int GrabSize = ui->spinBox_GrabSize->value();
        m_Grabber.OnGrab(GrabSize);
    }
}
