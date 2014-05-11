#include "QGuiCallbacks.h"



QDoubleValueChanged::QDoubleValueChanged(const DoubleValueChangedCallbackType &Callback, QObject *parent)
    : QObject(parent)
    , m_Callback(Callback)
{
}

void QDoubleValueChanged::OnValueChanged(double Value)
{
    m_Callback(Value);
}
