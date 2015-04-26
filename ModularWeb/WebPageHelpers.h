#pragma once

class CModuleManager;
class CWebPageManager;
class CPatchManager;
class CCommandStackController;

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController& CommandStackController);

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateCommandsPage(CWebPageManager& WebPageManager);

void UpdatePatchesPage(CPatchManager& PatchManager, CWebPageManager& WebPageManager);

void UpdateMainPage(CWebPageManager& WebPageManager);
