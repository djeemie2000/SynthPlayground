#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <deque>
#include <map>
#include <functional>
#include <string>

using namespace std;

struct SCmdStackItem
{
    std::string s_Name;
    bool s_BoolValue;
    int s_IntValue;
    float s_FloatValue;

    SCmdStackItem();

    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue);
};

typedef std::deque<SCmdStackItem> CmdStack;

typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::map<std::string, CmdFunction> CmdFunctionMap;
typedef std::map<std::string, SCmdStackItem> CmdStackMap;

#endif // COMMANDSTACK_H
