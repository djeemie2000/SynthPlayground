#include <iostream>
#include "LogCommandStackHandler.h"

CLogCommandStackHandler::CLogCommandStackHandler()
{
}

void CLogCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    std::cout << "Handling Item " << Item.s_Name << " (" << Item.s_BoolValue << "," << Item.s_IntValue << "," << Item.s_FloatValue << ")" << std::endl;//TODO
}
