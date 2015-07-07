#pragma once

#include <string>
#include "json11.hpp"

class CModuleManager;
class CPatchManager;

std::string PatchesToJson(const CPatchManager& PatchManager);

std::string ModulesToJson(const CModuleManager& ModuleManager);


