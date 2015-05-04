#pragma once

#include <string>
#include <vector>

class CPatchManager
{
public:
    CPatchManager(const std::string& PatchDirectory);

    void Update();
    std::vector<std::string> GetPatchNames() const;
    std::string GetPath(const std::string& PatchName) const;

private:
    const std::string m_PatchDirectory;
    std::vector<std::string> m_PatchNames;
};
