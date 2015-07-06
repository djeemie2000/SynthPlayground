#include <iostream>
#include <string>
#include <csignal>
#include "Pitch.h"
#include "ModularWebController.h"
#include "mongoose.h"
#include "WebPageManager.h"
#include "WebRequest.h"

namespace
{

void DoInstantiations()
{
    CPitch Pitch;
}

volatile std::sig_atomic_t gSignalStatus = 0;

}

void Usage()
{
    std::cout << "Usage: exe path_to_patch" << std::endl;
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

        SWebRequest Request = CreateWebRequest(conn);

        std::string Page = Controller->HandleWebRequest(Request);
        mg_printf_data(conn, "%s", Page.c_str());//reply

        // debug:
        LogWebRequest(Request, std::cout);

        RetVal =  MG_TRUE;
    }
        break;
    default:
        RetVal = MG_FALSE;
    }

    return RetVal;
}

void signal_handler(int Signal)
{
    gSignalStatus = Signal;
}

int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        // setup
        std::string PatchesDirectory(argv[1]);
        CModularWebController Controller(PatchesDirectory);

        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
        std::signal(SIGILL, signal_handler);
        std::signal(SIGSEGV, signal_handler);
        std::signal(SIGFPE, signal_handler);
        std::signal(SIGABRT, signal_handler);

        struct mg_server *server;

        // Create and configure the server
        server = mg_create_server(&Controller, ev_handler);
        mg_set_option(server, "listening_port", "8080");

        // Serve request. Hit Ctrl-C to terminate the program
        printf("Starting on port %s\n", mg_get_option(server, "listening_port"));

        // Run

        // detect ctrl-C or other signals
        while(gSignalStatus==0)
        {
            mg_poll_server(server, 1000);
        }

        std::cout << "Captured signal " << gSignalStatus << std::endl;

        // Cleanup, and free server instance
        std::cout << "Destroying server" << std::endl;
        mg_destroy_server(&server);

        return 0;

    }

    Usage();
    return -1;
}

