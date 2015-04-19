#pragma once

#include <string>
#include <map>
#include <ostream>

class mg_connection;

struct SWebRequest
{
    std::string s_Uri;
    std::map<std::string, std::string> s_Query;
};

SWebRequest CreateWebRequest(mg_connection* conn);
void LogWebRequest(const SWebRequest& Request, std::ostream& Oss);
