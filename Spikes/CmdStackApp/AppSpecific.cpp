#include "AppSpecific.h"

CAppSpecificController::CAppSpecificController()
{
}

void CAppSpecificController::BoolCommand1(bool Value)
{
    std::cout << "BoolCommand1 " << Value << std::endl;
}

void CAppSpecificController::BoolCommand2(bool Value)
{
    std::cout << "BoolCommand2 " << Value << std::endl;
}

void CAppSpecificController::IntCommand1(int Value)
{
    std::cout << "IntCommand1 " << Value << std::endl;
}

void CAppSpecificController::IntCommand2(int Value)
{
    std::cout << "IntCommand2 " << Value << std::endl;
}

void CAppSpecificController::FloatCommand1(float Value)
{
    std::cout << "FloatCommand1 " << Value << std::endl;
}

void CAppSpecificController::FloatCommand2(float Value)
{
    std::cout << "FloatCommand2 " << Value << std::endl;
}

void CAppSpecificController::Command1()
{
    std::cout << "Command1 (no value)" << std::endl;
}

CmdFunctionMap BuildAppSpecificCmdFunctionMap(CAppSpecificController& Controller)
{
    CmdFunctionMap FunctionMap;
    FunctionMap["Internal/Param1"] = [&Controller](const SCmdStackItem& Item){ Controller.BoolCommand1(Item.s_BoolValue);} ;
    FunctionMap["Internal/BoolCmd2"] = [&Controller](const SCmdStackItem& Item){ Controller.BoolCommand2(Item.s_BoolValue);} ;
    FunctionMap["Internal/Param2"] = [&Controller](const SCmdStackItem& Item){ Controller.IntCommand1(Item.s_IntValue);} ;
    FunctionMap["Internal/Param4"] = [&Controller](const SCmdStackItem& Item){ Controller.IntCommand2(Item.s_IntValue);} ;
    FunctionMap["Internal/Param3"] = [&Controller](const SCmdStackItem& Item){ Controller.FloatCommand1(Item.s_FloatValue);} ;
    FunctionMap["Internal/FloatCmd2"] = [&Controller](const SCmdStackItem& Item){ Controller.FloatCommand2(Item.s_FloatValue);} ;
    FunctionMap["Internal/Param5"] = [&Controller](const SCmdStackItem& ){ Controller.Command1();} ;
    return FunctionMap;
}

CmdStack BuildAppSpecificDefaults()
{
    CmdStack DefaultStack;
    DefaultStack.push_back({ "Internal/Param1", true, 0, 0.0f});
    DefaultStack.push_back({ "Internal/Param2", true, 10, 0.0f});
    DefaultStack.push_back({ "Internal/Param3", true, 0, 12.34f});
    DefaultStack.push_back({ "Internal/Param4", true, 2, 0.0f});
    DefaultStack.push_back({ "Internal/Param5", false, 0, 0.0f});
    return DefaultStack;
}
