#include "WebPageHelpers.h"
#include "WebPageManager.h"
#include "ModuleManager.h"

void UpdateModulesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager)
{
    std::string Content;
    Content += "<h3>Modules</h3>";
    auto ModuleNames = ModuleManager.GetNames();
    for(const auto& Name : ModuleNames)
    {
        Content += Name;
        Content += "<br>";
    }
    WebPageManager.Add("/Modules", Content);
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
