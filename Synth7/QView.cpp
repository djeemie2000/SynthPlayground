#include "QView.h"

QView::QView(QObject *parent) :
    QObject(parent)
{
}

void QView::SetSampleSize(int Size)
{
    emit SignalSampleRange(0, Size);
    emit SignalSampleSize(Size);
}

void QView::SetSample(const IView::SampleContainerType &Sample)
{
    SignalSample(QVector<std::int16_t>::fromStdVector(Sample));
}
