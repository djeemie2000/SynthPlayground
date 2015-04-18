#include <sstream>
#include "WebPageHelpers.h"
#include "WebPageManager.h"
#include "ModuleManager.h"
#include "ModularModuleI.h"
#include "WebPageModuleParameterVisitor.h"

void UpdateModulesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::string Content;
    Content += "<h3>Modules</h3>";
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        Content += "<a href=\"/Module/" + Name + "\" >" + Name + "</a>";
        Content += "<br>";
    }
    WebPageManager.Add("/Modules", Content);

    //add individual module pages
    for(const auto& Name : ModuleNames)
    {

        if(std::shared_ptr<IModularModule> Module = ModuleManager.GetModule(Name).lock())
        {
            std::string ModuleContent;
            ModuleContent += "<h3>" + Name + "</h3>";

            ModuleContent += "<h4>Inputs</h4>";
            for(const auto& Input : Module->GetInputNames())
            {
                ModuleContent += Input;
                ModuleContent += "<br>";
            }
            ModuleContent += "<h4>MidiInputs</h4>";
            for(const auto& Input : Module->GetMidiInputNames())
            {
                ModuleContent += Input;
                ModuleContent += "<br>";
            }
            ModuleContent += "<h4>Outputs</h4>";
            for(const auto& Input : Module->GetOutputNames())
            {
                ModuleContent += Input;
                ModuleContent += "<br>";
            }

            // TODO parameter visitor
            CWebPageModuleParameterVisitor Visitor;
            Module->Accept(Visitor);
            ModuleContent += Visitor.GetContent();

            WebPageManager.Add("/Module/"+Name, ModuleContent);
        }
    }
}

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::string Content;
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
    WebPageManager.Add("/SupportedModules", Content);
}


void UpdateCommandsPage(CWebPageManager &WebPageManager)
{
    std::ostringstream Content;
    Content << "<a href=\"/Commands/RemoveAll\" >RemoveAll</a><br>";
    Content << "<a href=\"/Commands/Default\" >Default</a><br>";
    WebPageManager.Add("/Commands", Content.str());
}
