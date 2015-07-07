#include "JsonHelpers.h"
#include "PatchManager.h"
#include "ModuleManager.h"
#include "ModularModuleI.h"

std::string PatchesToJson(const CPatchManager& PatchManager)
{
    json11::Json::array Patches;
    auto PatchNames = PatchManager.GetPatchNames();
    for(const auto& PatchName : PatchNames)
    {
        json11::Json::object Patch;
        Patch["Name"] = PatchName;
        Patch["path"] = PatchManager.GetPath(PatchName);
        Patches.push_back(Patch);
        //Patches.push_back({ {"name", PatchName}, {"path", PatchManager.GetPath(PatchName)} });
    }
    json11::Json Tmp = {{ "patches", Patches }};
    return Tmp.dump();
}

std::string ModulesToJson(const CModuleManager& ModuleManager)
{
    json11::Json::array Modules;
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& ModuleName : ModuleNames)
    {
        if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(ModuleName).lock())
        {
            json11::Json::object ModuleJson;
            ModuleJson["name"] = Module->GetName();
            ModuleJson["type"] = "unknown";

            json11::Json::array Connectors;
            for(const auto& Conn : Module->GetInputNames())
            {
                Connectors.push_back(json11::Json::object{ {"name", Conn}, {"type", "audio"}, {"mode", "in"} });
            }
            for(const auto& Conn : Module->GetOutputNames())
            {
                Connectors.push_back(json11::Json::object{ {"name", Conn}, {"type", "audio"}, {"mode", "out"} });
            }
            for(const auto& Conn : Module->GetMidiInputNames())
            {
                Connectors.push_back(json11::Json::object{ {"name", Conn}, {"type", "midi"}, {"mode", "in"} });
            }
            for(const auto& Conn : Module->GetMidiOutputNames())
            {
                Connectors.push_back(json11::Json::object{ {"name", Conn}, {"type", "midi"}, {"mode", "out"} });
            }
            ModuleJson["connectors"] = Connectors;

            Modules.push_back(ModuleJson);
        }
    }
    json11::Json Tmp = {{"modules", Modules}};
    return Tmp.dump();
}


