#include <iostream>
#include <fstream>
#include <map>
#include "CommandStackItem.h"

SCmdStackItem::SCmdStackItem()
    : s_Name()
    , s_BoolValue(false)
    , s_IntValue(-1)
    , s_FloatValue(-1.0f)
{
}

SCmdStackItem::SCmdStackItem(const string &Name)
    : s_Name(Name)
    // other members use member value initialisation
{
}

SCmdStackItem::SCmdStackItem(const std::string& Name, const std::string& Type, const std::string& Value)
 : s_Name(Name)
 // other members use member value initialisation
{
    TypeFromString(Type);
    ValueFromString(Value);
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

string SCmdStackItem::Value() const
{
    if(s_Type==BoolType)
    {
        return std::to_string(s_BoolValue);
    }
    else if(s_Type==IntType)
    {
        return std::to_string(s_IntValue);
    }
    else if(s_Type==FloatType)
    {
        return std::to_string(s_FloatValue);
    }
    else if(s_Type == TextType)
    {
        return s_TextValue;
    }
    return "";
}

string SCmdStackItem::Type() const
{
    if(s_Type==BoolType)
    {
        return "Boolean";
    }
    else if(s_Type==IntType)
    {
        return "Integer";
    }
    else if(s_Type==FloatType)
    {
        return "Float";
    }
    else if(s_Type == TextType)
    {
        return "Text";
    }
    return "";
}

void SCmdStackItem::TypeFromString(const std::string &Type)
{
    if(Type == "Boolean")
    {
        s_Type = BoolType;
    }
    else if(Type == "Integer")
    {
        s_Type = IntType;
    }
    else if(Type == "Float")
    {
        s_Type = FloatType;
    }
    else if(Type == "Text")
    {
        s_Type = TextType;
    }
    else
    {
        s_Type = UnknownType;
    }
}
