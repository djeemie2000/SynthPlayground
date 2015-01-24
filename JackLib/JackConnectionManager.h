#ifndef JACKCONNECTIONMANAGER_H
#define JACKCONNECTIONMANAGER_H

#include <string>
#include <vector>
#include <list>
#include <memory>
#include "IConnectionChangedListener.h"
#include "JackWin32Port.h"
#include <jack/jack.h>

class IConnectionChangedListener;

class CJackConnectionManager
{
public:
    typedef std::vector<std::string> PortNamesType;

    struct SConnection
    {
        std::string s_OutputPortName;
        std::string s_InputPortName;
    };

    typedef std::vector<SConnection> ConnectionsType;

    CJackConnectionManager();
    ~CJackConnectionManager();

    bool OpenClient(const std::string& ClientName);
    bool ClientIsOpen() const;

    PortNamesType GetAllPorts() const;
    PortNamesType GetInputPorts() const;
    PortNamesType GetOutputPorts() const;

    ConnectionsType GetConnections() const;
    PortNamesType GetConnectedPorts(const std::string& PortName) const;
    bool Connect(const std::string& OutputPortName, const std::string& InputPortName);
    bool Disconnect(const std::string& OutputPortName, const std::string& InputPortName);

    std::string GetPortDescription(const std::string& PortName) const;

    void Register(SPConnectionChangedListener Listener);
    void Unregister(SPConnectionChangedListener Listener);

    void CloseClient();

    void OnConnectionChanged(jack_port_id_t a, jack_port_id_t b, int Connect);

private:
    jack_client_t*  m_Client;
    std::list<SPConnectionChangedListener> m_Listeners;
};

std::string ConnectionsToString(const CJackConnectionManager& Manager);
bool StringToConnections(CJackConnectionManager& Manager, const std::string& ConnectionsString);
bool DisconnectAll(CJackConnectionManager& Manager);

std::string PortNameToClientName(const std::string& FullPortName);
std::string PortNameToInOutName(const std::string& FullPortName);

#endif // JACKCONNECTIONMANAGER_H
