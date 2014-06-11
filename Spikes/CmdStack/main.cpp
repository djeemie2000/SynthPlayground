#include <iostream>
#include <deque>
#include <vector>
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

    SCmdStackItem()
        : s_Name()
        , s_BoolValue(false)
        , s_IntValue(-1)
        , s_FloatValue(-1.0f)
    {}

    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue)
        : s_Name(Name)
        , s_BoolValue(BoolValue)
        , s_IntValue(IntValue)
        , s_FloatValue(FloatValue)
    {}
};

typedef std::deque<SCmdStackItem> CmdStack;

typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::map<std::string, CmdFunction> CmdFunctionMap;

void ExecuteCmdStack(CmdStack& Stack, const CmdFunctionMap& FunctionMap)
{
    for(auto& Item : Stack)
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

class CDummyController
{
public:
    CDummyController(){}

    void BoolCommand1(bool Value)
    {
        std::cout << "BoolCommand1 " << Value << std::endl;
    }

    void BoolCommand2(bool Value)
    {
        std::cout << "BoolCommand2 " << Value << std::endl;
    }

    void IntCommand1(int Value)
    {
        std::cout << "IntCommand1 " << Value << std::endl;
    }

    void IntCommand2(int Value)
    {
        std::cout << "IntCommand2 " << Value << std::endl;
    }

    void FloatCommand1(float Value)
    {
        std::cout << "FloatCommand1 " << Value << std::endl;
    }

    void FloatCommand2(float Value)
    {
        std::cout << "FloatCommand2 " << Value << std::endl;
    }

};

void BuildCmdFunctionMap(CDummyController& Controller, CmdFunctionMap& FunctionMap)
{
    FunctionMap["DummyController/BoolCmd1"] = [&Controller](const SCmdStackItem& Item){ Controller.BoolCommand1(Item.s_BoolValue);} ;
    FunctionMap["DummyController/BoolCmd2"] = [&Controller](const SCmdStackItem& Item){ Controller.BoolCommand2(Item.s_BoolValue);} ;
    FunctionMap["DummyController/IntCmd1"] = [&Controller](const SCmdStackItem& Item){ Controller.IntCommand1(Item.s_IntValue);} ;
    FunctionMap["DummyController/IntCmd2"] = [&Controller](const SCmdStackItem& Item){ Controller.IntCommand2(Item.s_IntValue);} ;
    FunctionMap["DummyController/FloatCmd1"] = [&Controller](const SCmdStackItem& Item){ Controller.FloatCommand1(Item.s_FloatValue);} ;
    FunctionMap["DummyController/FloatCmd2"] = [&Controller](const SCmdStackItem& Item){ Controller.FloatCommand2(Item.s_FloatValue);} ;
}

void TestCmdFunctionMap(const CmdFunctionMap& FunctionMap, const SCmdStackItem& Item)
{
    for(auto& Function : FunctionMap)
    {
        std::cout << "Testing Cmd " << Function.first << ": " << std::endl;
        Function.second(Item);
    }
}

void ExportCurrent(const CmdStack& Current)
{
    for(auto& Item : Current)
    {
        std::cout << "Exporting: Name=" << Item.s_Name
                  << " BoolValue=" << Item.s_BoolValue
                  << " IntValue=" << Item.s_IntValue
                  << " FloatValue=" << Item.s_FloatValue
                  << std::endl;
    }
}


typedef std::map<std::string, SCmdStackItem> CmdStackMap;

void UpdateCurrent(const CmdStack& Stack, CmdStackMap& Current)
{
    for(auto& Item : Stack)
    {
        Current[Item.s_Name] = Item;
    }
}

void ExtractCurrentStack(const CmdStackMap& Current, CmdStack& CurrentStack)
{
    for(auto& Item : Current)
    {
        CurrentStack.push_back(Item.second);
    }
}

int main()
{
    cout << "Hello World!" << endl;


    CDummyController Controller;
    CmdFunctionMap FunctionMap;
    BuildCmdFunctionMap(Controller, FunctionMap);

    std::cout << "Testing CmdFunction map " << std::endl;
    TestCmdFunctionMap(FunctionMap, { "0", true, 2, 3.0f});

    CmdStack Stack;
    Stack.push_back({ "DummyController/BoolCmd1", true, 2, 3.0f});
    Stack.push_back({ "DummyController/BoolCmd1", false, 2, 3.0f});
    Stack.push_back({ "DummyController/BoolCmd2", true, 2, 3.0f});
    Stack.push_back({ "DummyController/BoolCmd2", false, 2, 3.0f});
    Stack.push_back({ "DummyController/IntCmd1", true, 2, 3.0f});
    Stack.push_back({ "DummyController/IntCmd1", true, -2, 3.0f});
    Stack.push_back({ "DummyController/IntCmd2", true, 2, 3.0f});
    Stack.push_back({ "DummyController/IntCmd2", true, -2, 3.0f});
    Stack.push_back({ "DummyController/FloatCmd1", true, 2, 3.0f});
    Stack.push_back({ "DummyController/FloatCmd1", true, 2, -3.0f});
    Stack.push_back({ "DummyController/FloatCmd2", true, 2, 3.0f});
    Stack.push_back({ "DummyController/FloatCmd2", true, 2, -3.0f});

    std::cout << "Executing Cmd stack" << std::endl;
    ExecuteCmdStack(Stack, FunctionMap);

    std::cout << "Updating current commands with Cmd stack" << std::endl;
    CmdStackMap Current;
    UpdateCurrent(Stack, Current);

    std::cout << "Exporting current Cmd stack" << std::endl;
    CmdStack CurrentStack;
    ExtractCurrentStack(Current, CurrentStack);
    ExportCurrent(CurrentStack);

    std::cout << "Executing current Cmd stack" << std::endl;
    ExecuteCmdStack(CurrentStack, FunctionMap);

    return 0;
}

