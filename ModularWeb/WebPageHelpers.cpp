#include <sstream>
#include "WebPageHelpers.h"
#include "WebPageManager.h"
#include "ModuleManager.h"
#include "ModularModuleI.h"
#include "WebPageModuleParameterVisitor.h"
#include "PatchManager.h"

void UpdateModulesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    {
        std::ostringstream Content;
        Content << "<!DOCTYPE html><html><head><title>Modules</title></head><body>";

        Content << "<h3>Modules</h3>";
        auto ModuleNames = ModuleManager.GetNames();
        for(const auto& Name : ModuleNames)
        {
            Content << "<a href=\"/Module/" << Name << "\" >" << Name << "</a>";
            Content << "<br>";
        }
        Content << "</body></html>";
        WebPageManager.Add("/Modules", Content.str());
    }

    //add individual module pages
    {
        auto ModuleNames = ModuleManager.GetNames();
        for(const auto& Name : ModuleNames)
        {
            if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(Name).lock())
            {
                std::ostringstream ModuleContent;
                ModuleContent << "<!DOCTYPE html><html><head><title>" << Name << "</title></head><body>";
                ModuleContent << "<h3>" << Name << "</h3>";

                ModuleContent << "<h4>Inputs</h4>";
                for(const auto& Input : Module->GetInputNames())
                {
                    ModuleContent << Input;
                    ModuleContent << "<br>";
                }
                ModuleContent << "<h4>MidiInputs</h4>";
                for(const auto& Input : Module->GetMidiInputNames())
                {
                    ModuleContent << Input;
                    ModuleContent << "<br>";
                }
                ModuleContent << "<h4>Outputs</h4>";
                for(const auto& Input : Module->GetOutputNames())
                {
                    ModuleContent << Input;
                    ModuleContent << "<br>";
                }

                CWebPageModuleParameterVisitor Visitor;
                Module->Accept(Visitor);
                ModuleContent << Visitor.GetContent();

                ModuleContent << "</body></html>";

                WebPageManager.Add("/Module/"+Name, ModuleContent.str());
            }
        }
    }
}

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::string Content;
    Content += "<!DOCTYPE html><html><head><title>SupportedModules</title></head><body>";
    Content += "<h3>Supported Modules</h3>";
    auto ModuleCategories = ModuleManager.GetSupportedCategories();
    for(const auto& Category : ModuleCategories)
    {
        Content += "<h4>";
        Content += Category;
        Content += "</h4>";

        auto ModuleTypes = ModuleManager.GetSupportedTypes(Category);
        for(const auto& Type : ModuleTypes)
        {
            Content += Type;
            Content += "<br>";
        }
    }
    Content += "</body></html>";
    WebPageManager.Add("/SupportedModules", Content);
}


void UpdateCommandsPage(CWebPageManager &WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>Commands</title></head><body>";
    Content << "<a href=\"/Commands/RemoveAll\" >RemoveAll</a><br>";
    Content << "<a href=\"/Commands/Default\" >Default</a><br>";
    Content << "</body></html>";
    WebPageManager.Add("/Commands", Content.str());
}


void UpdatePatchesPage(CPatchManager &PatchManager, CWebPageManager &WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>Patches</title></head><body><h3>Patches</h3><table border=\"1\"><tr><th>Patch</th><th>Load</th><th>Path</th></tr>";
    for(const std::string& Patch : PatchManager.GetPatchNames())
    {
        Content << "<tr><td>" << Patch << "</td><td><a href=\"/Commands/Load/" << Patch << "\" >Load</a></td><td>" << PatchManager.GetPath(Patch) << "</td></tr>";
    }
    Content << "</table></body></html>";
    WebPageManager.Add("/Patches", Content.str());
}
