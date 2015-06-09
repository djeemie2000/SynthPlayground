#ifndef QGRAPHBUFFERHANDLER_H
#define QGRAPHBUFFERHANDLER_H

#include <QObject>
#include <QVector>
#include <QPointF>
#include "BufferHandlerI.h"

class QGraphBufferHandler : public QObject, public IBufferHandler<float>
{
    Q_OBJECT
public:
    explicit QGraphBufferHandler(QObject *parent = 0);

    bool HandleBuffer(const float *Buffer, int Size) override;

signals:
    void SignalGraph(QVector<QPointF> Points);
public slots:
};

#endif // QGRAPHBUFFERHANDLER_H
