#ifndef QGraphWidget_H
#define QGraphWidget_H

#include <QVector>
#include <QPointF>
#include <QPen>
#include <QWidget>

class QGraphWidget : public QWidget
{
    Q_OBJECT

public:
    QGraphWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const /*Q_DECL_OVERRIDE*/;
    QSize sizeHint() const /*Q_DECL_OVERRIDE*/;

public slots:
    void setPen(const QPen &Pen);
    void setAxisPen(const QPen &Pen);
    void setAntialiased(bool Antialiased);
    void setGraph(QVector<QPointF> Points);

protected:
    void paintEvent(QPaintEvent *event) /*Q_DECL_OVERRIDE*/;

private:
    QPen m_Pen;
    QPen m_AxisPen;
    bool m_Antialiased;

    QVector<QPointF> m_Points;
};

#endif // QGraphWidget_H
