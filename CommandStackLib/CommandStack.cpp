#include <iostream>
#include <fstream>
#include "CommandStack.h"

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
