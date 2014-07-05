#ifndef QSCOPE_H
#define QSCOPE_H

#include <QObject>
#include <QVector>
#include "ScopeI.h"

class QInt16Scope : public QObject, public IInt16Scope
{
    Q_OBJECT
public:
    explicit QInt16Scope(QObject *parent = 0);

    void SetSample(const SampleContainerType& Sample) override;

signals:
    void SignalSample(QVector<std::int16_t> Sample);
};

class QFloatScope : public QObject, public IScope<float>
{
    Q_OBJECT
public:
    explicit QFloatScope(QObject *parent = 0);

    void SetSample(const SampleContainerType& Sample) override;

signals:
    void SignalSample(QVector<float> Sample);
};

#endif // QSCOPE_H
