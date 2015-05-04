#include "WebPageManager.h"



CWebPageManager::CWebPageManager()
 : m_Pages()
 , m_DefaultPage()//TODO some usable default page!
{

}

void CWebPageManager::Clear()
{
    m_Pages.clear();
}

void CWebPageManager::AddPage(const std::string &Uri, const std::string &Content)
{
    m_Pages[Uri] = Content;
}

void CWebPageManager::AddDefaultPage(const std::string &Content)
{
    m_DefaultPage = Content;
}

std::string CWebPageManager::GetPage(const std::string &Uri)
{
    auto itPage = m_Pages.find(Uri);
    return itPage != m_Pages.end() ? itPage->second : m_DefaultPage;
}
