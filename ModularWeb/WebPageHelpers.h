#pragma once

class CModuleManager;
class CWebPageManager;
class CPatchManager;
class CCommandStackController;

void CreatePages(CWebPageManager& WebPageManager);

void UpdatePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController& CommandStackController);

// TODO private:

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController& CommandStackController);

void UpdateModuleTypesPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdateCommandsPage(CWebPageManager& WebPageManager);

void UpdatePatchesPage(CPatchManager& PatchManager, CWebPageManager& WebPageManager);

void UpdateTestPage(CWebPageManager& WebPageManager);
