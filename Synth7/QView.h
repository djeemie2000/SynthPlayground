#ifndef QGRANULARSAMPLERVIEW_H
#define QGRANULARSAMPLERVIEW_H

#include <QObject>
#include <QVector>
#include "View.h"

class QView : public QObject, public IView
{
    Q_OBJECT
public:
    explicit QView(QObject *parent = 0);

    void SetSampleSize(int Size) override;

    void SetSample(const SampleContainerType& Sample) override;

signals:
    void SignalSampleSize(int Size);
    void SignalSampleRange(int Begin, int End);
    void SignalSample(QVector<std::int16_t> Sample);

public slots:

};

#endif // QGRANULARSAMPLERVIEW_H
