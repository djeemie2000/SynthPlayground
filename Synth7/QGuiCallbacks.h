#ifndef QGUICALLBACKS_H
#define QGUICALLBACKS_H

#include <QObject>
#include <functional>

typedef std::function<void(double)> DoubleValueChangedCallbackType;
typedef std::function<void(int)> IntValueChangedCallbackType;

class QDoubleValueChanged : public QObject
{
    Q_OBJECT
public:
    explicit QDoubleValueChanged(const DoubleValueChangedCallbackType& Callback, QObject *parent = 0);

public slots:
    void OnValueChanged(double Value);

private:
    DoubleValueChangedCallbackType m_Callback;
};

#endif // QGUICALLBACKS_H
