#include "QGraphWidget.h"
#include <QPainter>

QGraphWidget::QGraphWidget(QWidget *parent)
    : QWidget(parent)
    , m_Pen(Qt::green, 0)
    , m_AxisPen(Qt::red, 0)
{
    m_Antialiased = true;

    // the following will create a black background:
    setBackgroundRole(QPalette::WindowText);
    setAutoFillBackground(true);
}

QSize QGraphWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize QGraphWidget::sizeHint() const
{
    return QSize(400, 200);
}

void QGraphWidget::setPen(const QPen &Pen)
{
    m_Pen = Pen;
    update();
}

void QGraphWidget::setAxisPen(const QPen &Pen)
{
    m_AxisPen = Pen;
}

void QGraphWidget::setAntialiased(bool antialiased)
{
    m_Antialiased = antialiased;
    update();
}

void QGraphWidget::setGraph(QVector<QPointF> Points)
{
    m_Points = Points;
    update();
}

void QGraphWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    if (m_Antialiased)
    {
        painter.setRenderHint(QPainter::Antialiasing, true);
    }


    float ScaleX = 1.0f;
    if(!m_Points.empty())
    {
        ScaleX *= width();
        ScaleX /= m_Points.size();
    }
    painter.save();
    painter.translate(0, height()/2);
    painter.scale(ScaleX, height()/3);

    painter.setPen(m_AxisPen);
    painter.drawLine(QPointF(0,0), QPointF(m_Points.size(),0));
    painter.drawLine(QPointF(0,-1), QPointF(m_Points.size(),-1));
    painter.drawLine(QPointF(0,1), QPointF(m_Points.size(),1));

    painter.setPen(m_Pen);
    painter.drawPolyline(m_Points.data(), m_Points.size());

    painter.restore();

    painter.setBrush(Qt::NoBrush);
}
