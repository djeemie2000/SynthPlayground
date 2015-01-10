#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <cstdint>
#include <deque>
#include <map>
#include <functional>
#include <string>

using namespace std;

struct SCmdStackItem
{
    std::string s_Name{};
    bool s_BoolValue{false};
    int s_IntValue{-1};
    float s_FloatValue{-1.0f};
    std::uint32_t s_TimeStamp{0};
    bool s_HasTimeStamp{false};

    SCmdStackItem();

    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue);
    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue, std::uint32_t TimeStamp);
    explicit SCmdStackItem(const std::string& Name);

    SCmdStackItem &Name(const std::string& Name);
    SCmdStackItem &BoolValue(bool Value);
    SCmdStackItem &IntValue(int Value);
    SCmdStackItem &FloatValue(float Value);
    SCmdStackItem &TimeStamp(std::uint32_t TimeStamp);

    const std::string& Name() const;
    bool BoolValue() const;
    int IntValue() const;
    float FloatValue() const;
    std::uint32_t TimeStamp() const;
};

typedef std::deque<SCmdStackItem> CmdStack;

typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::map<std::string, CmdFunction> CmdFunctionMap;
typedef std::map<std::string, SCmdStackItem> CmdStackMap;

#endif // COMMANDSTACK_H
