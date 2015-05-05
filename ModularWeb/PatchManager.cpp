#include <algorithm>
#include "PatchManager.h"
#include "FileSystemHelpers.h"

CPatchManager::CPatchManager(const std::string &PatchDirectory)
 : m_PatchDirectory(PatchDirectory)
 , m_PatchNames()
{
    Update();
}

void CPatchManager::Update()
{
    m_PatchNames.clear();

    std::vector<std::string> FileNames;
    if(ListDirectory(m_PatchDirectory, FileNames))
    {
        // Patch filename = somename.xml <=> patch name = somename
        for(const auto& FileName : FileNames)
        {
            std::size_t Pos = FileName.rfind(".xml");
            if(Pos!=std::string::npos)
            {
                std::string PatchName = FileName.substr(0, Pos);
                m_PatchNames.push_back(PatchName);
            }
        }
    }

    // order patch names alphabetically
    std::sort(m_PatchNames.begin(), m_PatchNames.end());
}

std::vector<std::string> CPatchManager::GetPatchNames() const
{
    return m_PatchNames;
}

std::string CPatchManager::GetPath(const std::string &PatchName) const
{
    if(std::find(m_PatchNames.begin(), m_PatchNames.end(), PatchName)!=m_PatchNames.end())
    {
        return CreatePath(PatchName);
    }
    return std::string();
}

std::string CPatchManager::CreatePath(const std::string &PatchName) const
{
    // Patch filename = somename.xml <=> patch name = somename
    return m_PatchDirectory + "/" + PatchName + ".xml";
}
