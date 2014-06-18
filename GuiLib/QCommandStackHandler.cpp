#include <iostream>
#include "QCommandStackHandler.h"

QCommandStackHandler::QCommandStackHandler(QObject *parent) :
    QObject(parent)
{
}

void QCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    std::cout << "Feedback to gui: Item "
              << Item.s_Name << " ("
              << Item.s_BoolValue << ","
              << Item.s_IntValue << ","
              << Item.s_FloatValue << ")" << std::endl;

    emit SignalBoolValueChanged(Item.s_BoolValue);
    emit SignalIntValueChanged(Item.s_IntValue);
    emit SignalDoubleValueChanged(Item.s_FloatValue);
    emit SignalChanged();
}
