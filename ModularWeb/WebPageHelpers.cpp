#include <sstream>
#include "WebPageHelpers.h"
#include "WebPageManager.h"
#include "ModuleManager.h"
#include "ModularModuleI.h"
#include "WebPageModuleParameterVisitor.h"
#include "PatchManager.h"

void UpdateModulePage(const CModuleManager& ModuleManager, const std::string& Name, CWebPageManager& WebPageManager)
{
    if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(Name).lock())
    {
        std::ostringstream ModuleContent;
        ModuleContent << "<!DOCTYPE html><html><head><title>" << Name << "</title></head><body>";
        ModuleContent << "<h3>" << Name << "</h3>";

        std::vector<std::string> Column1;
        Column1.push_back("--------");

        auto t1 = Module->GetInputNames();
        Column1.insert(Column1.end(), t1.begin(), t1.end());

        Column1.push_back("--Midi--");
        auto t2 = Module->GetMidiInputNames();
        Column1.insert(Column1.end(), t2.begin(), t2.end());

        std::vector<std::string> Column2;
        Column2.push_back("--------");
        auto t3 = Module->GetOutputNames();
        Column2.insert(Column2.end(), t3.begin(), t3.end());
        Column2.push_back("--Midi--");

        if(Column1.size()<Column2.size())
        {
            Column1.resize(Column2.size());
        }
        else
        {
            Column2.resize(Column1.size());
        }

        ModuleContent << "<table border=\"1\"><tr><th>Inputs</th><th>Outputs</th></tr>";
        for(std::size_t idx = 0; idx<Column1.size(); ++idx)
        {
            ModuleContent << "<tr><td>" << Column1[idx] << "</td><td>" << Column2[idx] << "</td></tr>";
        }
        ModuleContent << "</table>";

        CWebPageModuleParameterVisitor Visitor;
        Module->Accept(Visitor);
        ModuleContent << Visitor.GetContent();

        ModuleContent << "</body></html>";

        WebPageManager.Add("/Module/"+Name, ModuleContent.str());
    }
}

void UpdateModuleOverviewPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>Modules</title></head><body>";

    Content << "<h3>Modules</h3><table border=\"1\" >";
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        Content << "<tr><td><a href=\"/Module/" << Name << "\" >" << Name << "</a></td></tr>";
    }
    Content << "</table></body></html>";
    WebPageManager.Add("/Modules", Content.str());
}

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    UpdateModuleOverviewPage(ModuleManager, WebPageManager);

    //add individual module pages
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        UpdateModulePage(ModuleManager, Name, WebPageManager);
    }
}

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>SupportedModules</title></head><body>";
    Content << "<h3>Supported Modules</h3>";
    Content << "<table border=\"1\" >";
    auto ModuleCategories = ModuleManager.GetSupportedCategories();
    for(const auto& Category : ModuleCategories)
    {
        Content << "<tr><th>" << Category << "</th></tr>";

        auto ModuleTypes = ModuleManager.GetSupportedTypes(Category);
        for(const auto& Type : ModuleTypes)
        {
            Content << "<tr><td>" << Type << "</td></tr>";
        }
    }
    Content << "</table></body></html>";
    WebPageManager.Add("/SupportedModules", Content.str());
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
