#include <iostream>
#include <fstream>
#include "CommandStackItem.h"

SCmdStackItem::SCmdStackItem()
    : s_Name()
    , s_BoolValue(false)
    , s_IntValue(-1)
    , s_FloatValue(-1.0f)
{
}

SCmdStackItem::SCmdStackItem(const string &Name, bool BoolValue, int IntValue, float FloatValue)
    : s_Name(Name)
    , s_BoolValue(BoolValue)
    , s_IntValue(IntValue)
    , s_FloatValue(FloatValue)
    , s_TimeStamp(0)
    , s_HasTimeStamp(false)
{
}

SCmdStackItem::SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue, std::uint32_t TimeStamp)
    : s_Name(Name)
    , s_BoolValue(BoolValue)
    , s_IntValue(IntValue)
    , s_FloatValue(FloatValue)
    , s_TimeStamp(TimeStamp)
    , s_HasTimeStamp(true)
{
}

SCmdStackItem::SCmdStackItem(const string &Name)
    : s_Name(Name)
    // other members use member value initialisation
{
}

SCmdStackItem &SCmdStackItem::Name(const string &Name)
{
    s_Name = Name;
    return *this;
}

SCmdStackItem &SCmdStackItem::BoolValue(bool Value)
{
    s_BoolValue = Value;
    s_Type = BoolType;
    return *this;
}

SCmdStackItem &SCmdStackItem::IntValue(int Value)
{
    s_IntValue = Value;
    s_Type = IntType;
    return *this;
}

SCmdStackItem &SCmdStackItem::FloatValue(float Value)
{
    s_FloatValue = Value;
    s_Type = FloatType;
    return *this;
}

SCmdStackItem &SCmdStackItem::TimeStamp(std::uint32_t TimeStamp)
{
    s_TimeStamp = TimeStamp;
    s_HasTimeStamp = true;
    return *this;
}

SCmdStackItem &SCmdStackItem::TextValue(const string &TextValue)
{
    s_TextValue = TextValue;
    s_Type = TextType;
    return *this;
}

const string &SCmdStackItem::Name() const
{
    return s_Name;
}

bool SCmdStackItem::BoolValue() const
{
    return s_BoolValue;
}

int SCmdStackItem::IntValue() const
{
    return s_IntValue;
}

float SCmdStackItem::FloatValue() const
{
    return s_FloatValue;
}

std::uint32_t SCmdStackItem::TimeStamp() const
{
    return s_TimeStamp;
}

const string &SCmdStackItem::TextValue() const
{
    return s_TextValue;
}

SCmdStackItem &SCmdStackItem::ValueFromString(const string &String)
{
    if(s_Type==BoolType)
    {
        try
        {
            s_BoolValue = (0!=std::stoi(String));
        }
        catch(...)
        {
        }
    }
    else if(s_Type == IntType)
    {
        try
        {
            s_IntValue = std::stoi(String);
        }
        catch(...)
        {
        }
    }
    else if(s_Type == FloatType)
    {
        try
        {
            s_FloatValue = std::stof(String);
        }
        catch(...)
        {
        }
    }
    else if(s_Type == TextType)
    {
        s_TextValue = String;
    }

    return *this;
}
