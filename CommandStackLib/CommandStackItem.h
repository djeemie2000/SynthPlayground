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
    static const int UnknownType = 0;
    static const int BoolType = 1;
    static const int IntType = 2;
    static const int FloatType = 3;
    static const int TextType = 4;

    std::string s_Name{};
    bool s_BoolValue{false};
    int s_IntValue{-1};
    float s_FloatValue{-1.0f};
    std::string s_TextValue{};
    int s_Type{UnknownType};

    SCmdStackItem();

    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue);
    explicit SCmdStackItem(const std::string& Name);

    SCmdStackItem &Name(const std::string& Name);
    SCmdStackItem &BoolValue(bool Value);
    SCmdStackItem &IntValue(int Value);
    SCmdStackItem &FloatValue(float Value);
    SCmdStackItem &TextValue(const std::string& TextValue);

    const std::string& Name() const;
    bool BoolValue() const;
    int IntValue() const;
    float FloatValue() const;
    const std::string& TextValue() const;

    SCmdStackItem &ValueFromString(const std::string& String);
};

typedef std::deque<SCmdStackItem> CmdStack;

typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::map<std::string, CmdFunction> CmdFunctionMap;
typedef std::map<std::string, SCmdStackItem> CmdStackMap;

#endif // COMMANDSTACK_H
