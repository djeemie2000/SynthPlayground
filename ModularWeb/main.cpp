#include <iostream>
#include <string>
#include "Pitch.h"
#include "ModularWebController.h"

#include "mongoose.h"
#include "WebPageManager.h"

namespace
{

void DoInstantiations()
{
    CPitch Pitch;
}

}

void Usage()
{
    std::cout << "exe path_to_patch" << std::endl;
}


static int ev_handler(struct mg_connection *conn, enum mg_event ev)
{
    int RetVal = MG_FALSE;

    switch (ev)
    {
    case MG_AUTH:
        RetVal = MG_TRUE;
        break;
    case MG_REQUEST:
    {
        CModularWebController* Controller = (CModularWebController*)conn->server_param;
        std::string Page = Controller->HandleWebRequest(conn->uri);
        mg_printf_data(conn, "%s", Page.c_str());
        RetVal =  MG_TRUE;
    }
        break;
    default:
        RetVal = MG_FALSE;
    }

    return RetVal;
}


int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        std::string Path(argv[1]);
        CModularWebController Controller;

        Controller.Load(Path);
        std::cout << "Opened patch " << Path << std::endl;

        if(true)
        {
            struct mg_server *server;

            // Create and configure the server
            server = mg_create_server(&Controller, ev_handler);
            mg_set_option(server, "listening_port", "8080");

            // Serve request. Hit Ctrl-C to terminate the program
            printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
            for (;;)
            {
                mg_poll_server(server, 1000);
                // can we detect keypressed or ctrl-C here?????
            }

            // Cleanup, and free server instance
            std::cout << "Destroying server" << std::endl;
            mg_destroy_server(&server);
        }
        else
        {
            std::cout << "Opened patch " << Path << std::endl;
            std::cout << "Press 'q' to exit" << std::endl;
            // wait for key 'q'
            char Key = ' ';
            std::cin >> Key;
        }
        return 0;

    }

    Usage();
    return -1;
}

