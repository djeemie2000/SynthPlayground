#ifndef ICONNECTIONCHANGEDLISTENER_H
#define ICONNECTIONCHANGEDLISTENER_H

#include <string>
#include <memory>

class IConnectionChangedListener
{
public:
    virtual ~IConnectionChangedListener(){}

    virtual void OnConnectionChanged(const std::string& OutputPortName, const std::string& InputPortName, bool Connect) =0;
};

typedef std::shared_ptr<IConnectionChangedListener> SPConnectionChangedListener;

#endif // ICONNECTIONCHANGEDLISTENER_H
