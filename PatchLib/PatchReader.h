#pragma once

#include <string>

class CCommandStack;
class CJackConnectionManager;
class CModuleManager;

class CPatchReader
{
public:
    CPatchReader();

    bool ReadPatch(const std::string& Path,
                        CCommandStack& CommandStack,
                        CModuleManager& ModuleManager,
                        CJackConnectionManager& ConnectionManager);

private:
};
