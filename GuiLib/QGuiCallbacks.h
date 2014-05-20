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

class QBoolValueChanged : public QObject
{
    Q_OBJECT
public:
    explicit QBoolValueChanged(const guiutils::BoolValueChangedCallbackType& Callback, QObject *parent = 0);

public slots:
    void OnValueChanged(bool Value);

private:
    guiutils::BoolValueChangedCallbackType m_Callback;
};

class QSomethingHappened : public QObject
{
    Q_OBJECT
public:
    explicit QSomethingHappened(const guiutils::SimpleCallbackType& Callback, QObject *parent = 0);

public slots:
    void OnSomethingHappened();

private:
    guiutils::SimpleCallbackType m_Callback;
};


#endif // QGUICALLBACKS_H
