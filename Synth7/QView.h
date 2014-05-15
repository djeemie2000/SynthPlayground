#ifndef QSCOPE_H
#define QSCOPE_H

#include <QObject>
#include <QVector>
#include "ScopeI.h"

class QScope : public QObject, public IScope
{
    Q_OBJECT
public:
    explicit QScope(QObject *parent = 0);

    void SetSample(const SampleContainerType& Sample) override;

signals:
    void SignalSample(QVector<std::int16_t> Sample);

public slots:

};

#endif // QSCOPE_H
