#pragma once

#include <string>
#include <map>

class CWebPageManager
{
public:
    CWebPageManager();

    void Clear();
    void Add(const std::string& Path, const std::string& Content);
    std::string Get(const std::string& Path);

private:
    std::map<std::string, std::string> m_Pages;
};
