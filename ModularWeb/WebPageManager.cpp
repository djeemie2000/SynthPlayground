#include "WebPageManager.h"



CWebPageManager::CWebPageManager()
 : m_Pages()
{

}

void CWebPageManager::Clear()
{
    m_Pages.clear();
}

void CWebPageManager::Add(const std::string &Path, const std::string &Content)
{
    m_Pages[Path] = Content;
}

std::string CWebPageManager::Get(const std::string &Path)
{
    std::string DefaultContent = "Request uri was " + Path;

    auto itPage = m_Pages.find(Path);
    return itPage != m_Pages.end() ? itPage->second : DefaultContent;
}
