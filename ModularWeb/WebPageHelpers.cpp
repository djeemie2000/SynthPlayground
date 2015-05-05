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
                <li><a href="Modules">CurrentModules</a></li>
                <li><a href="ModuleCreation">ModuleManagement</a></li>
                <li><a href="Connections">Connections</a></li>
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

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController &CommandStackController)
{
    auto ModuleNames = ModuleManager.GetNames();

    std::ostringstream Content;
    Content << R"(
   <div class="row">

   <div class="col-sm-2">
   <form>
   <div class="btn-group-vertical">
   <input type="submit" class="btn btn-info" name="Command" value="RemoveAll" >
   <input type="submit" class="btn btn-info" name="Command" value="DefaultAll" >
   <input type="submit" class="btn btn-info" name="Command" value="Remove" >
   <input type="submit" class="btn btn-info" name="Command" value="Default" >
   </div>
   <div class ="container">
   )";

    for(const auto& Name : ModuleNames)
    {
        Content << R"( <input type="radio" name="SelectedModule" value=")" << Name << R"(" >)" << Name << "<br>";
    }
    Content << R"(
   </div>
   </form>
   </div>
   <div class="col-sm-10">
    )";

    for(const auto& Name : ModuleNames)
    {
        Content << R"(<div class="panel panel-default"><div class="panel-heading">)" << Name << R"(</div><div class="panel-body">)";
        if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(Name).lock())
        {
            CWebPageModuleParameterVisitor Visitor(CommandStackController);
            Module->Accept(Visitor);
            Content << Visitor.GetContent();
        }
        Content << "</div></div>";
    }
    Content << "</div></div>";

    WebPageManager.AddPage("/Modules", GetCommonBegin()+Content.str()+GetCommonEnd());
}

void UpdateModuleCreationPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::ostringstream Content;
    Content << R"(<form><div class="row"><div class="col-sm-12">)";
    Content << R"(<input type="submit" class="btn btn-info" name="Command" value="Create" >)";
    Content << R"(</div></div><div class="row">)";

    auto ModuleCategories = ModuleManager.GetSupportedCategories();
    std::size_t CategoryIndex = 0;
    for(std::size_t Column = 0; Column<6; ++Column)
    {
        Content << R"(<div class="col-sm-2"><div class="container">)";

        for(int idx = 0; idx<2; ++idx)
        {
            if(CategoryIndex<ModuleCategories.size())
            {
                auto Category = ModuleCategories[CategoryIndex];
                Content << "<h4>" << Category << "</h4>";
                auto ModuleTypes = ModuleManager.GetSupportedTypes(Category);
                for(const auto& Type : ModuleTypes)
                {
                    Content << R"(<input type="radio" name="SelectedModule" value=")" << Type << R"(" >)" << Type << "<br>";
                }
            }
            ++CategoryIndex;
        }

        Content << "</div></div>";
    }

    Content << "</form></div>";

    WebPageManager.AddPage("/ModuleCreation", GetCommonBegin()+Content.str()+GetCommonEnd());
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
                Content << R"(<div class="col-sm-3">)";
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
