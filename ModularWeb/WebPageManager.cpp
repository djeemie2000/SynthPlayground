#include "WebPageManager.h"



CWebPageManager::CWebPageManager()
 : m_Pages()
{

}

void CWebPageManager::Clear()
{
    m_Pages.clear();
}

void CWebPageManager::Add(const std::string &Uri, const std::string &Content)
{
    m_Pages[Uri] = Content;
}

std::string CWebPageManager::Get(const std::string &Uri)
{
    std::string DefaultContent = "Request uri was " + Uri;

    auto itPage = m_Pages.find(Uri);
    return itPage != m_Pages.end() ? itPage->second : DefaultContent;
}
