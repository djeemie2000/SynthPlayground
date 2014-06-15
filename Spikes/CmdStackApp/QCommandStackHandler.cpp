#include "QCommandStackHandler.h"

QCommandStackHandler::QCommandStackHandler(QObject *parent) :
    QObject(parent)
{
}

void QCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    emit SignalBoolValueChanged(Item.s_BoolValue);
    emit SignalIntValueChanged(Item.s_IntValue);
    emit SignalDoubleValueChanged(Item.s_FloatValue);
    emit SignalChanged();
}
