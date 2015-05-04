#include <sstream>
#include "WebPageHelpers.h"
#include "WebPageManager.h"
#include "ModuleManager.h"
#include "ModularModuleI.h"
#include "WebPageModuleParameterVisitor.h"
#include "PatchManager.h"

namespace
{

std::string GetCommonBegin()
{
    return R"(
            <!DOCTYPE html>
            <html lang="en">
            <head>
              <title>ModularWeb</title>
              <meta charset="utf-8">
              <meta name="viewport" content="width=device-width, initial-scale=1">
              <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css">
              <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js"></script>
              <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
            </head>
            <body>

            <div class="row bg-primary">
            <div class="page-header text-center">
            <h1>WebModular</h1>
            </div>
            </div>
            <!end of header row>

            <div class="row">
            <div class="col-sm-12">
            <ul class="pagination">
                <li><a href="Patches">Patches</a></li>
                <li><a href="Modules.html">CurrentModules</a></li>
                <li><a href="ModuleCreation.html">ModuleManagement</a></li>
                <li><a href="Connections.html">Connections</a></li>
            </ul>
            </div>
            </div>
            <!end of navigation row>
           )";
}

std::string GetCommonEnd()
{
    return R"(
            <div class="row">
            <div class="col-sm-12 text-center bg-primary">
            ...TODO...
            </div>
            </div>
            <!end of footer row>

            </body>
            </html>
           )";
}

}//namespace

void UpdateModulePage(const CModuleManager& ModuleManager, const std::string& Name, CWebPageManager& WebPageManager, CCommandStackController &CommandStackController)
{
    if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(Name).lock())
    {
        std::ostringstream ModuleContent;
        ModuleContent << "<!DOCTYPE html><html><head><title>" << Name << "</title></head><body>";
        ModuleContent << "<h3>" << Name << "</h3>";

        std::vector<std::string> Column0;
        Column0.push_back("Audio/Control");

        auto Column1 = Module->GetInputNames();

        auto Column2 = Module->GetOutputNames();

        std::size_t MaxSize = std::max(Column0.size(), std::max(Column1.size(), Column2.size()));
        Column0.resize(MaxSize);
        Column1.resize(MaxSize);
        Column2.resize(MaxSize);

        Column0.push_back("Midi");

        auto t1 = Module->GetMidiInputNames();
        Column1.insert(Column1.end(), t1.begin(), t1.end());

        auto t2 = Module->GetMidiOutputNames();
        Column2.insert(Column2.end(), t2.begin(), t2.end());

        MaxSize = std::max(Column0.size(), std::max(Column1.size(), Column2.size()));
        Column0.resize(MaxSize);
        Column1.resize(MaxSize);
        Column2.resize(MaxSize);

        ModuleContent << "<table border=\"1\"><tr><th></th><th>Inputs</th><th>Outputs</th></tr>";
        for(std::size_t idx = 0; idx<Column1.size(); ++idx)
        {
            ModuleContent << "<tr><td>" << Column0.at(idx)
                          << "</td><td>" << Column1.at(idx)
                          << "</td><td>"<< Column2.at(idx)
                          << "</td></tr>";
        }
        ModuleContent << "</table>";

        CWebPageModuleParameterVisitor Visitor(CommandStackController);
        Module->Accept(Visitor);
        ModuleContent << Visitor.GetContent();

        ModuleContent << "</body></html>";

        WebPageManager.AddPage("/Module/"+Name, ModuleContent.str());
    }
}

void UpdateModuleOverviewPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>Modules</title></head><body>";

    Content << "<h3>Modules</h3><table border=\"1\" >";
    Content << "<tr><th>Module</th><th>Remove</th></tr>";
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        Content << "<tr>"
                << "<td><a href=\"/Module/" << Name << "\" >" << Name << "</a></td>"
                << R"(<td><form ><input type="submit" name="Remove" value=")" << Name << R"(" ></form></td>)"
                << "</tr>";
    }
    Content << "</table></body></html>";
    WebPageManager.AddPage("/Modules", Content.str());
}

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController &CommandStackController)
{
    UpdateModuleOverviewPage(ModuleManager, WebPageManager);

    //add individual module pages
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        UpdateModulePage(ModuleManager, Name, WebPageManager, CommandStackController);
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
            Content << R"(<tr><td><form ><input type="submit" name="Create" value=")" << Type << R"(" ></form></td></tr>)";
        }
    }
    Content << "</table></body></html>";
    WebPageManager.AddPage("/SupportedModules", Content.str());
}


void UpdateCommandsPage(CWebPageManager &WebPageManager)
{
    std::ostringstream Content;
    Content << "<!DOCTYPE html><html><head><title>Commands</title></head><body>";
    Content << R"(<form ><input type="submit" name="Command" value="RemoveAll" ></form>)";
    Content << R"(<form ><input type="submit" name="Command" value="Default" ></form>)";
    Content << "</body></html>";
    WebPageManager.AddPage("/Commands", Content.str());
}


void UpdatePatchesPage(CPatchManager &PatchManager, CWebPageManager &WebPageManager)
{
    std::ostringstream Content;
    Content << R"(
               <div class="row">
               <div class="col-sm-12">
               <form>
               <div class="btn-group">
               <input type="submit" class="btn btn-info" name="Command" value="Load" >
               <input type="submit" class="btn btn-info" name="Command" value="Save" >
               <input type="submit" class="btn btn-info" name="Command" value="Clear" >
               <input type="submit" class="btn btn-info" name="Command" value="SaveAs" >
               </div>
               <input type="text" name="PatchName" >
               <div class="container">
            )";

    auto PatchNames = PatchManager.GetPatchNames();
    std::size_t ColumnSize = PatchNames.size()/4;
    for(std::size_t idx = 0; idx<PatchNames.size(); ++idx)
    {
        if(idx%ColumnSize==0)
        {
            if(idx!=0)
            {
                Content << R"(</div><div class="col-sm-3">)";
            }
            else
            {
                Content << R"(<div class="col-sm-2">)";
            }
        }
        Content << R"(<input type="radio" name="SelectedPatch" value=")" << PatchNames[idx] << R"(" >)" << PatchNames[idx] << "<br>";
    }
    Content << "</div>";

    Content << R"(
               </div>
               </form>
               </div>
               </div>
               <!end of patches row>
               )";


    WebPageManager.AddPage("/Patches", GetCommonBegin()+Content.str()+GetCommonEnd());
}

void UpdateTestPage(CWebPageManager &WebPageManager)
{
    std::ostringstream Content;

    Content << R"(<!DOCTYPE html>
                 <html>
                 <body>

                 <form>
                 <select name="ParameterName">
                 <option value="0">Volvo</option>
                 <option value="1" selected>Saab</option>
                 <option value="2">Fiat</option>
                 <option value="3">Audi</option>
                 </select>
                 <br><br>
                 <input type="submit">
                 </form>

                 </body>
                 </html>)";

    WebPageManager.AddPage("/test", Content.str());
}


void AddDefaultPage(CWebPageManager& WebPageManager)
{
    std::string Default = R"(
            <div class="row">
            <div class="col-sm-12 text-center">
            <div class="jumbotron bg-warning"
            <h3>Unknown page</h3>
            </div>
            </div>
            </div>
            <!end of default row>
            )";
    WebPageManager.AddDefaultPage(GetCommonBegin()+Default+GetCommonEnd());
}

void CreatePages(CWebPageManager &WebPageManager)
{
    AddDefaultPage(WebPageManager);
}
