#pragma once

#include <string>
#include <map>

class CCommandStack;
class CJackConnectionManager;
class CModuleManager;

class CPatchWriter
{
public:
    CPatchWriter();

    bool WritePatch(const std::string& Path,
                    const CCommandStack& CommandStack,
                    const CModuleManager& ModuleManager,
                    const CJackConnectionManager& ConnectionManager);

private:
};
