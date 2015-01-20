#ifndef QCONNECTIONCHANGEDLISTENER_H
#define QCONNECTIONCHANGEDLISTENER_H

#include <QObject>
#include <QString>
#include "IConnectionChangedListener.h"

class QConnectionChangedListener : public QObject,
                                    public IConnectionChangedListener
{
    Q_OBJECT
public:
    explicit QConnectionChangedListener(QObject *parent = 0);

    void OnConnectionChanged(const std::string& OutputPortName, const std::string& InputPortName, bool Connect) override;

signals:
    void SignalConnectionChanged(QString OutputPortName, QString InputPortName, bool Connect);

public slots:

};

#endif // QCONNECTIONCHANGEDLISTENER_H
