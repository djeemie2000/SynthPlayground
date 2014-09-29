#ifndef JACKCONNECTIONMANAGER_H
#define JACKCONNECTIONMANAGER_H

#include <string>
#include <vector>
#include "JackWin32Port.h"
#include <jack/jack.h>

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
    bool Connect(const std::string& OutputPortName, const std::string& InputPortName);
    bool Disconnect(const std::string& OutputPortName, const std::string& InputPortName);

    std::string GetPortDescription(const std::string& PortName) const;

    void CloseClient();

private:
    jack_client_t*  m_Client;
};

std::string ConnectionsToString(const CJackConnectionManager& Manager);
bool StringToConnections(CJackConnectionManager& Manager, const std::string& ConnectionsString);
bool DisconnectAll(CJackConnectionManager& Manager);

#endif // JACKCONNECTIONMANAGER_H
