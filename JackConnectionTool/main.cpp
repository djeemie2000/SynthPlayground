#include <iostream>
#include "JackConnectionManager.h"

using namespace std;

void PrintNames(const std::vector<std::string>& Names)
{
    for(const auto& Name : Names)
    {
        std::cout << Name << std::endl;
    }
}

int main()
{
    CJackConnectionManager Manager;
    Manager.OpenClient("JackConnectionTool");

    std::cout << "All ports: " << std::endl;
    PrintNames(Manager.GetAllPorts());
    std::cout << "Input ports: " << std::endl;
    PrintNames(Manager.GetInputPorts());
    std::cout << "Output ports: " << std::endl;
    PrintNames(Manager.GetOutputPorts());

    // TODO print all descriptions

    // print all connections
    std::cout << "Connections: " << std::endl;
    std::string CurrentConnections = ConnectionsToString(Manager);
    std::cout <<  CurrentConnections;

    // disconnect all current connections
    std::cout << "Disconnect all: " << std::endl;
    DisconnectAll(Manager);
    std::cout << ConnectionsToString(Manager);

    // re-connect all connections
    std::cout << "Reconnect all: " << std::endl;
    StringToConnections(Manager, CurrentConnections);
    std::cout << ConnectionsToString(Manager);

    Manager.CloseClient();

    return 0;
}

