#pragma once

class CModuleManager;
class CWebPageManager;

void UpdateModulesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateCommandsPage(CWebPageManager& WebPageManager);
