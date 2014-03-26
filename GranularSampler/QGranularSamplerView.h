#ifndef QGRANULARSAMPLERVIEW_H
#define QGRANULARSAMPLERVIEW_H

#include <QObject>
#include <QVector>
#include "GranularSamplerView.h"

class QGranularSamplerView : public QObject, public IGranularSamplerView
{
    Q_OBJECT
public:
    explicit QGranularSamplerView(QObject *parent = 0);

    void SetSampleSize(int Size) override;

    void SetSample(const SampleContainerType& Sample) override;

signals:
    void SignalSampleSize(int Size);
    void SignalSampleRange(int Begin, int End);
    void SignalSample(QVector<std::uint8_t> Sample);

public slots:

};

#endif // QGRANULARSAMPLERVIEW_H
