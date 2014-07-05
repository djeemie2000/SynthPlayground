#include "QScope.h"

QInt16Scope::QInt16Scope(QObject *parent)
    : QObject(parent)
{
}

void QInt16Scope::SetSample(const IInt16Scope::SampleContainerType &Sample)
{
    SignalSample(QVector<std::int16_t>::fromStdVector(Sample));
}


QFloatScope::QFloatScope(QObject *parent)
: QObject(parent)
{
}

void QFloatScope::SetSample(const SampleContainerType &Sample)
{
    SignalSample(QVector<float>::fromStdVector(Sample));
}
