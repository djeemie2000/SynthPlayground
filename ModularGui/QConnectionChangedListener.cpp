#include "QConnectionChangedListener.h"

QConnectionChangedListener::QConnectionChangedListener(QObject *parent) :
    QObject(parent)
{
}

void QConnectionChangedListener::OnConnectionChanged(const std::string &OutputPortName, const std::string &InputPortName, bool Connect)
{
    emit SignalConnectionChanged(QString::fromStdString(OutputPortName), QString::fromStdString(InputPortName), Connect);
}
