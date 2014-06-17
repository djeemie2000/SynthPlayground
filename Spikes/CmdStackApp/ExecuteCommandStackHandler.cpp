#include <iostream>
#include "ExecuteCommandStackHandler.h"

CExecuteCommandStackHandler::CExecuteCommandStackHandler(const CmdFunctionMap &FunctionMap)
 : m_FunctionMap(FunctionMap)
{
}

namespace
{

void ExecuteCmdStackItem(const SCmdStackItem& Item, const CmdFunctionMap& FunctionMap)
{
    auto itFunction = FunctionMap.find(Item.s_Name);
    if(itFunction!=FunctionMap.end())
    {
        itFunction->second(Item); //execute function stack item ~Name
    }
    else
    {
        std::cout << "Error! executing unknown function " << Item.s_Name << std::endl;
    }
}

}

void CExecuteCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    ExecuteCmdStackItem(Item, m_FunctionMap);
}

void CExecuteCommandStackHandler::Add(const string &Name, const CmdFunction &Function)
{
    m_FunctionMap[Name] = Function;
    // check for overwrites?
}
