#pragma once

class CModuleManager;
class CWebPageManager;
class CPatchManager;
class CCommandStackController;

void CreatePages(CWebPageManager& WebPageManager);

void UpdatePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController& CommandStackController);

// TODO private:

void UpdateModulePages(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager, CCommandStackController& CommandStackController);

void UpdateModuleCreationPage(const CModuleManager& ModuleManager, CWebPageManager& WebPageManager);

void UpdatePatchesPage(CPatchManager& PatchManager, CWebPageManager& WebPageManager);
