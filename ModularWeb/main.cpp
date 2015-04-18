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

void Usage()
{

}

}

static int ev_handler(struct mg_connection *conn, enum mg_event ev)
{
    int RetVal = MG_FALSE;
    switch (ev) {
    case MG_AUTH:
        RetVal = MG_TRUE;
        break;
    case MG_REQUEST:
    {
        CWebPageManager* WebPageManager = (CWebPageManager*)conn->server_param;
        std::string Page = WebPageManager->Get(conn->uri);
        mg_printf_data(conn, "%s", Page.c_str());//"Hello! Requested URI is [%s]", conn->uri);
        RetVal =  MG_TRUE;
    }
        break;
    default:
        RetVal = MG_FALSE;
    }
    return RetVal;
}

void UpdateModulesPage(const CModularWebController& Controller, CWebPageManager& WebPageManager)
{
    std::string Content;
    Content += "<h3>Modules</h3>";
    auto ModuleNames = Controller.GetNames();
    for(const auto& Name : ModuleNames)
    {
        Content += Name;
        Content += "<br>";
    }
    WebPageManager.Add("/Modules", Content);
}

void UpdateModuleTypesPage(const CModularWebController& Controller, CWebPageManager& WebPageManager)
{
    std::string Content;
    Content += "<h3>Supported Modules</h3>";
    auto ModuleCategories = Controller.GetSupportedCategories();
    for(const auto& Category : ModuleCategories)
    {
        Content += "<h4>";
        Content += Category;
        Content += "</h4>";

        auto ModuleTypes = Controller.GetSupportedTypes(Category);
        for(const auto& Type : ModuleTypes)
        {
            Content += Type;
            Content += "<br>";
        }
    }
    WebPageManager.Add("/SupportedModules", Content);
}

int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        //TODO web stuff
        std::string Path(argv[1]);
        CModularWebController Controller;
        Controller.Load(Path);

        std::cout << "Opened patch " << Path << std::endl;

        CWebPageManager WebPageManager;
        UpdateModulesPage(Controller, WebPageManager);
        UpdateModuleTypesPage(Controller, WebPageManager);

        if(true)
        {
            struct mg_server *server;

            // Create and configure the server
            server = mg_create_server(&WebPageManager, ev_handler);
            mg_set_option(server, "listening_port", "8080");

            // Serve request. Hit Ctrl-C to terminate the program
            printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
            for (;;)
            {
                mg_poll_server(server, 1000);
                // can we detect keypressed or ctrl-C here?????
            }

            // Cleanup, and free server instance
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

