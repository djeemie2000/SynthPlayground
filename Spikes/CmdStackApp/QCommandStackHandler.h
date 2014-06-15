#ifndef QCOMMANDSTACKHANDLER_H
#define QCOMMANDSTACKHANDLER_H

#include <QObject>
#include "CommandStack.h"

class QCommandStackHandler : public QObject, public ICommandStackHandler
{
    Q_OBJECT
public:
    explicit QCommandStackHandler(QObject *parent = 0);

    void Handle(const SCmdStackItem& Item) override;

signals:
    void SignalBoolValueChanged(bool Value);
    void SignalIntValueChanged(int Value);
    void SignalDoubleValueChanged(double Value);
    void SignalChanged();

public slots:

};

#endif // QCOMMANDSTACKHANDLER_H
