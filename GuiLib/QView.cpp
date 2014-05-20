#include "QView.h"

QScope::QScope(QObject *parent) :
    QObject(parent)
{
}

void QScope::SetSample(const IScope::SampleContainerType &Sample)
{
    SignalSample(QVector<std::int16_t>::fromStdVector(Sample));
}
