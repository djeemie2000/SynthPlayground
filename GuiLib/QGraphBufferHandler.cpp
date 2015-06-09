#include "QGraphBufferHandler.h"

QGraphBufferHandler::QGraphBufferHandler(QObject *parent) : QObject(parent)
{
}

bool QGraphBufferHandler::HandleBuffer(const float *Buffer, int Size)
{
    QVector<QPointF> Points;
    for(int idx = 0; idx<Size; ++idx)
    {
        Points.push_back(QPointF(idx, Buffer[idx]));
    }

    emit SignalGraph(Points);

    return true;
}

