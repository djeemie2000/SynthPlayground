#pragma once

#include <string>
#include <map>

class CWebPageManager
{
public:
    CWebPageManager();

    void Clear();
    void AddPage(const std::string& Uri, const std::string& Content);
    void AddDefaultPage(const std::string& Content);

    std::string GetPage(const std::string& Uri);

private:
    std::map<std::string, std::string> m_Pages;
    std::string m_DefaultPage;
};
