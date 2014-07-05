#include <iostream>
#include "QScopeWidget2.h"
#include "ui_QScopeWidget2.h"
#include "PeriodicSampleGrabberI.h"

QScopeWidget2::QScopeWidget2(IPeriodicSampleGrabber& Grabber, QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::QScopeWidget2)
  , m_Grabber(Grabber)
{
    ui->setupUi(this);

    QGraphicsScene* Scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(Scene);

    Scene->setForegroundBrush(QColor(0,0,0,92));

    ui->graphicsView->show();
}

QScopeWidget2::~QScopeWidget2()
{
    delete ui;
}

void QScopeWidget2::SetSample(const SampleContainerType &Sample)
{
    std::cout << "deprecated! Sample size = " << Sample.size() << std::endl;


//    if(!Sample.empty())
//    {
//        if(QGraphicsScene* Scene = ui->graphicsView->scene())
//        {
//            // clear all previous items
//            QList<QGraphicsItem*> Items = Scene->items();
//            for(auto Item : Items)
//            {
//                Scene->removeItem(Item);
//            }

//            // center around 'middle' of sample
//            int Offset = -Sample.size()/2;

//            // show red line as x axis
//            QPen Pen(Qt::red);
//            Pen.setWidth(3);
//            Scene->addLine(Offset, 0, Offset+Sample.size(), 0, Pen);

//            // show min and max amplitude lines
//            const int Scaling = 128;
//            Scene->addLine(Offset, -Scaling, Offset+Sample.size(), -Scaling, QPen(Qt::red));
//            Scene->addLine(Offset, Scaling, Offset+Sample.size(), Scaling, QPen(Qt::red));

//            // show sample as path
//            QPainterPath Path;
//            Path.moveTo(Offset, -Sample.at(0)*Scaling);
//            int DeltaX = 4;
//            for(int x = 0; x<Sample.size(); x+=DeltaX)
//            {
//                // value increases ~ y decreases!
//                QPointF Pt(Offset+x, -Sample.at(x)*Scaling);
//                Path.lineTo(Pt);
//            }
//            Scene->addPath(Path, QPen(Qt::green));

//        }
//    }
}

void QScopeWidget2::OnSample(QVector<float> Sample)
{
    std::cout << "Sample size = " << Sample.size() << std::endl;

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
            const int Scaling = 128;
            Scene->addLine(Offset, -Scaling, Offset+Sample.size(), -Scaling, QPen(Qt::red));
            Scene->addLine(Offset, Scaling, Offset+Sample.size(), Scaling, QPen(Qt::red));

            // show sample as path
            QPainterPath Path;
            Path.moveTo(Offset, -Sample.at(0)*Scaling);
            int DeltaX = 4;
            for(int x = 0; x<Sample.size(); x+=DeltaX)
            {
                // value increases ~ y decreases!
                QPointF Pt(Offset+x, -Sample.at(x)*Scaling);
                Path.lineTo(Pt);
            }
            Scene->addPath(Path, QPen(Qt::green));

        }
    }
}

void QScopeWidget2::on_spinBox_GrabPeriod_valueChanged(int arg1)
{
    m_Grabber.OnGrabPeriod(arg1);
}

void QScopeWidget2::on_spinBox_GrabSize_valueChanged(int arg1)
{
    m_Grabber.OnGrabSize(arg1);
}

namespace
{

const float ZoomFactor = 1.1f;

}

void QScopeWidget2::on_toolButton_ZoomHorizontalIn_clicked()
{
    ui->graphicsView->scale(ZoomFactor, 1.0f);
}

void QScopeWidget2::on_toolButton_ZoomHorizontalOut_clicked()
{
    ui->graphicsView->scale(1/ZoomFactor, 1.0f);
}

void QScopeWidget2::on_toolButton_ZoomVerticalIn_clicked()
{
    ui->graphicsView->scale(1.0f, ZoomFactor);
}

void QScopeWidget2::on_toolButton_ZoomVerticalOut_clicked()
{
    ui->graphicsView->scale(1.0f, 1/ZoomFactor);
}
