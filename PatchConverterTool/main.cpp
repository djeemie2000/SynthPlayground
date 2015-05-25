#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <csignal>
#include "PatchManager.h"
#include "PatchWriter.h"
#include "ModuleFactory.h"
#include "ModuleManager.h"
#include "CommandStackController.h"
#include "JackConnectionManager.h"
#include "CommandStack.h"
#include "tinyxml2.h"

volatile std::sig_atomic_t gSignalStatus = 0;

void signal_handler(int Signal)
{
    gSignalStatus = Signal;
}

void Usage()
{
    std::cout << "Usage: exe Path" << std::endl;
}

std::string TiXmlElementToString(const tinyxml2::XMLElement* Element)
{
    if(Element && Element->GetText())
    {
        return Element->GetText();
    }
    return "";
}

int main(int argc, const char* argv[])
{
    if(2<=argc)
    {
        std::signal(SIGINT, signal_handler);
        std::signal(SIGTERM, signal_handler);
        std::signal(SIGILL, signal_handler);
        std::signal(SIGSEGV, signal_handler);
        std::signal(SIGFPE, signal_handler);
        std::signal(SIGABRT, signal_handler);

        // setup
        std::string Path(argv[1]);

        CPatchManager SrcPatchManager(Path);
        CPatchManager DstPatchManager(Path+"/Converted");

        //
        CJackConnectionManager ConnectionManager;
        ConnectionManager.OpenClient("ConnectionMgr");

        std::shared_ptr<CCommandStackController> CommandStackController(new CCommandStackController());
        std::shared_ptr<IModuleFactory> ModuleFactory(new CModuleFactory(CommandStackController));
        std::shared_ptr<CModuleManager> ModuleManager(new CModuleManager(ModuleFactory));

        auto PatchNames = SrcPatchManager.GetPatchNames();
        for(std::size_t idx = 0; idx<PatchNames.size(); ++idx)
        {
            auto PatchName = PatchNames[idx];
            std::cout << "Converting " << idx << "/" << PatchNames.size() << " : " << PatchName << "..." << std::endl;

            // parse patch into 3 strings:
            tinyxml2::XMLDocument Doc;
            if(tinyxml2::XML_NO_ERROR == Doc.LoadFile(SrcPatchManager.GetPath(PatchName).c_str()))
            {
                //TODO check path version -> if "2" => do not convert
                std::string Modules = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Modules") );
                std::string Connections = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Connections") );
                std::string Parameters = TiXmlElementToString( Doc.RootElement()->FirstChildElement("Parameters") );

                ModuleManager->Import(Modules);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                StringToConnections(ConnectionManager, Connections);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                CommandStackController->ImportFromString(Parameters);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));

                CCommandStack Tmp;
                Tmp.AddItems(CommandStackController->GetCurrent());
                bool Success = CPatchWriter().WritePatch(DstPatchManager.CreatePath(PatchName), Tmp, *ModuleManager, ConnectionManager);

                DisconnectAll(ConnectionManager);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                ModuleManager->RemoveAll();

                if(Success)
                {
                    std::cout << "Converted patch " << PatchName << std::endl;
                }
                else
                {
                    std::cout << "Failed to convert patch " << PatchName << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to read patch " << PatchName << std::endl;
            }


            // detect ctrl-C or other signals
            if(gSignalStatus!=0)
            {
                std::cout << "Captured signal " << gSignalStatus << std::endl;
                break;
            }
        }

        // cleanup
        ModuleManager.reset();
        ModuleFactory.reset();
        CommandStackController.reset();
        ConnectionManager.CloseClient();
        return 0;
    }

    Usage();
	return -1;
}

