#ifndef QGUICALLBACKS_H
#define QGUICALLBACKS_H

#include <QObject>
#include <functional>
#include "GuiUtilities.h"

class QDoubleValueChanged : public QObject
{
    Q_OBJECT
public:
    explicit QDoubleValueChanged(const guiutils::DoubleValueChangedCallbackType& Callback, QObject *parent = 0);

public slots:
    void OnValueChanged(double Value);

private:
    guiutils::DoubleValueChangedCallbackType m_Callback;
};

class QIntValueChanged : public QObject
{
    Q_OBJECT
public:
    explicit QIntValueChanged(const guiutils::IntValueChangedCallbackType& Callback, QObject *parent = 0);

public slots:
    void OnValueChanged(int Value);

private:
    guiutils::IntValueChangedCallbackType m_Callback;
};

#endif // QGUICALLBACKS_H
