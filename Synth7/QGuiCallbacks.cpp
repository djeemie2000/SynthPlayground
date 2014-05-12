#include "QGuiCallbacks.h"

QDoubleValueChanged::QDoubleValueChanged(const guiutils::DoubleValueChangedCallbackType &Callback, QObject *parent)
    : QObject(parent)
    , m_Callback(Callback)
{
}

void QDoubleValueChanged::OnValueChanged(double Value)
{
    m_Callback(Value);
}


QIntValueChanged::QIntValueChanged(const guiutils::IntValueChangedCallbackType &Callback, QObject *parent)
 : QObject(parent)
 , m_Callback(Callback)
{
}

void QIntValueChanged::OnValueChanged(int Value)
{
    m_Callback(Value);
}
