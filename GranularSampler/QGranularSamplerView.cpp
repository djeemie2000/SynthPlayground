#include "QGranularSamplerView.h"

QGranularSamplerView::QGranularSamplerView(QObject *parent) :
    QObject(parent)
{
}

void QGranularSamplerView::SetSampleSize(int Size)
{
    emit SignalSampleRange(0, Size);
    emit SignalSampleSize(Size);
}

void QGranularSamplerView::SetSample(const IGranularSamplerView::SampleContainerType &Sample)
{
    SignalSample(QVector<std::uint8_t>::fromStdVector(Sample));
}
