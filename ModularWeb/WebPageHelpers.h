#pragma once

class CModuleManager;
class CWebPageManager;
class CPatchManager;

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateCommandsPage(CWebPageManager& WebPageManager);

void UpdatePatchesPage(CPatchManager& PatchManager, CWebPageManager& WebPageManager);
