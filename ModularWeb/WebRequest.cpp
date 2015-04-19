#include <cstring>
#include <vector>
#include <algorithm>
#include "WebRequest.h"
#include "mongoose.h"

SWebRequest CreateWebRequest(mg_connection *conn)
{
    SWebRequest Request;

    Request.s_Uri = conn->uri;

    if(conn->query_string)
    {
        const int IsUrlEncoded = 1;
        const int MaxQuerySize = 512;
        std::vector<char> Temp(MaxQuerySize);
        mg_url_decode(conn->query_string, std::strlen(conn->query_string), Temp.data(), MaxQuerySize, IsUrlEncoded);

        // split Temp (format k=v&k=v&k=v ...) into key/value pairs
        bool Done = false;
        auto KeyStartPos = Temp.begin();
        while(!Done)
        {
            auto ValueStartPos = std::find(KeyStartPos, Temp.end(), '=');
            auto NextKeyStartPos = std::find(ValueStartPos, Temp.end(), '&');
            if(ValueStartPos!=Temp.end())
            {
                std::string Key(KeyStartPos, ValueStartPos);
                ++ValueStartPos;
                std::string Value(ValueStartPos, NextKeyStartPos);
                Request.s_Query[Key] = Value;
                KeyStartPos = NextKeyStartPos;
                ++KeyStartPos;
            }
            else
            {
                Done = true;
            }
        }

    }

    return Request;
}


void LogWebRequest(const SWebRequest &Request, std::ostream &Oss)
{
    Oss << "Request:" << std::endl << "Uri= " << Request.s_Uri << std::endl;
    for(const auto& Kv : Request.s_Query)
    {
        Oss << "Query: " << Kv.first << " = " << Kv.second << std::endl;
    }
    Oss << std::endl;

}
