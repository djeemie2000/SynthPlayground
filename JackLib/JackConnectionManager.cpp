#include <sstream>
#include <iostream>
#include "JackConnectionManager.h"

CJackConnectionManager::CJackConnectionManager()
 : m_Client(0)
{
}

CJackConnectionManager::~CJackConnectionManager()
{
    CloseClient();
}

bool CJackConnectionManager::OpenClient(const std::string &ClientName)
{
    // open client with requested name. No further options are needed
    m_Client = jack_client_open(ClientName.c_str(), JackNullOption, 0);
    return ClientIsOpen();
}

bool CJackConnectionManager::ClientIsOpen() const
{
    return 0!=m_Client;
}

namespace
{

CJackConnectionManager::PortNamesType GetPorts(jack_client_t* Client, unsigned int Flags)
{
    CJackConnectionManager::PortNamesType PortNames;

    if(Client)
    {
        if(const char** JackPortNames = jack_get_ports(Client, 0, 0, Flags))
        {
            int IdxPort = 0;
            while(JackPortNames[IdxPort])
            {
                PortNames.push_back(JackPortNames[IdxPort]);
                //jack_free((void*)JackPortNames[IdxPort]); //?????????
                ++IdxPort;
            }
        }
    }

    return PortNames;
}

}//namespace

CJackConnectionManager::PortNamesType CJackConnectionManager::GetAllPorts() const
{
    return GetPorts(m_Client, 0);
}

CJackConnectionManager::PortNamesType CJackConnectionManager::GetInputPorts() const
{
    return GetPorts(m_Client, JackPortIsInput);
}

CJackConnectionManager::PortNamesType CJackConnectionManager::GetOutputPorts() const
{
    return GetPorts(m_Client, JackPortIsOutput);
}

namespace
{

CJackConnectionManager::PortNamesType GetConnectedPorts(jack_client_t* Client, const std::string& PortName)
{
    CJackConnectionManager::PortNamesType ConnectedPortNames;

    if(Client)
    {
        if(jack_port_t* Port = jack_port_by_name(Client, PortName.c_str()))
        {
            if(const char** JackPortNames = jack_port_get_connections(Port))
            {
                int IdxPort = 0;
                while(JackPortNames[IdxPort])
                {
                    ConnectedPortNames.push_back(JackPortNames[IdxPort]);
                    //jack_free((void*)JackPortNames[IdxPort]); //?????????
                    ++IdxPort;
                }
            }
        }
    }

    return ConnectedPortNames;
}

}//namespace

CJackConnectionManager::ConnectionsType CJackConnectionManager::GetConnections() const
{
    ConnectionsType Connections;
    // enumerate all output ports (names)
    // for each output port: get all connected input ports (names)
    // for each connected input port: add a connection to the connections list
    PortNamesType OutputPortNames = GetOutputPorts();
    for(auto& PortName : OutputPortNames)
    {
        PortNamesType ConnectedPortNames = ::GetConnectedPorts(m_Client, PortName);
        for(auto& ConnectedPortName : ConnectedPortNames)
        {
            Connections.push_back({PortName, ConnectedPortName});
        }
    }

    return Connections;
}

CJackConnectionManager::PortNamesType CJackConnectionManager::GetConnectedPorts(const std::string &PortName) const
{
    return ::GetConnectedPorts(m_Client, PortName);
}

bool CJackConnectionManager::Connect(const std::string &OutputPortName, const std::string &InputPortName)
{
    bool Success = (0==jack_connect(m_Client, OutputPortName.c_str(), InputPortName.c_str()));
    std::cout << "Connecting " << OutputPortName << " to " << InputPortName << (Success ? " Ok" : " Failed!") << std::endl;
    return Success;
}

bool CJackConnectionManager::Disconnect(const std::string &OutputPortName, const std::string &InputPortName)
{
    bool Success = (0==jack_disconnect(m_Client, OutputPortName.c_str(), InputPortName.c_str()));
    std::cout << "Disconnecting " << OutputPortName << " from " << InputPortName << (Success ? " Ok" : " Failed!") << std::endl;
    return Success;
}

std::string CJackConnectionManager::GetPortDescription(const std::string &PortName) const
{
    if(m_Client)
    {
        std::ostringstream Oss;
        if(jack_port_t* Port = jack_port_by_name(m_Client, PortName.c_str()))
        {
            Oss << "Port : " << PortName;
            if(jack_port_flags(Port) & JackPortIsInput)
            {
                Oss << " - Input ";
            }
            if(jack_port_flags(Port) & JackPortIsOutput)
            {
                Oss << " - Output ";
            }
            Oss << " - " << jack_port_type(Port);
            if(jack_port_flags(Port) & JackPortIsPhysical)
            {
                Oss << " - Physical ";
            }
            if(jack_port_flags(Port) & JackPortIsTerminal)
            {
                Oss << " - Terminal ";
            }
        }
        return Oss.str();
    }
    return "";
}

void CJackConnectionManager::CloseClient()
{
    if(m_Client)
    {
        // close and remove the client
        jack_client_close(m_Client);
        // make sure we know we are closed
        m_Client = 0;
    }
}


std::string ConnectionsToString(const CJackConnectionManager &Manager)
{
    std::string ReturnValue;
    CJackConnectionManager::ConnectionsType Connections = Manager.GetConnections();
    for(auto& Connection : Connections)
    {
        ReturnValue += Connection.s_OutputPortName;
        ReturnValue += " -> ";
        ReturnValue += Connection.s_InputPortName;
        ReturnValue += "\n";
    }
    return ReturnValue;
}


bool DisconnectAll(CJackConnectionManager &Manager)
{
    bool AllDisconnected = true;
    CJackConnectionManager::ConnectionsType Connections = Manager.GetConnections();
    for(auto& Connection : Connections)
    {
        if(!Manager.Disconnect(Connection.s_OutputPortName, Connection.s_InputPortName))
        {
            AllDisconnected = false;
        }
    }
    return AllDisconnected;
}


bool StringToConnections(CJackConnectionManager &Manager, const std::string &ConnectionsString)
{
    bool AllConnected = true;

    std::istringstream Iss(ConnectionsString.c_str());
    do
    {
        std::string Line;
        std::getline(Iss, Line);
        if(4<=Line.length())
        {
            std::string OutputPortName = Line.substr(0, Line.find(" -> ", 0));
            std::string InputPortName = Line.substr(Line.find(" -> ", 0)+4, std::string::npos);
            if(!Manager.Connect(OutputPortName, InputPortName))
            {
                AllConnected = false;
            }
        }
    }
    while(!Iss.eof());

    return AllConnected;
}
