#include <iostream>
#include <deque>
#include <vector>
#include <functional>
#include <string>

using namespace std;

struct SCmdStackItem
{
    int s_Id;
    bool s_BoolValue;
    int s_IntValue;
    float s_FloatValue;

    SCmdStackItem()
        : s_Id(-1)
        , s_BoolValue(false)
        , s_IntValue(-1)
        , s_FloatValue(-1.0f)
    {}

    SCmdStackItem(int Id, bool BoolValue, int IntValue, float FloatValue)
        : s_Id(Id)
        , s_BoolValue(BoolValue)
        , s_IntValue(IntValue)
        , s_FloatValue(FloatValue)
    {}
};

typedef std::deque<SCmdStackItem> CmdStack;


typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::vector<CmdFunction> CmdFunctionList;


void ExecuteCmdStack(CmdStack& Stack, const CmdFunctionList& FunctionList)
{
    while(!Stack.empty())
    {
        SCmdStackItem& Item = Stack.front();
        FunctionList.at(Item.s_Id)(Item);//execute function stack item ~Id
        Stack.pop_front();
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


typedef std::vector<std::string> CmdNameList;
std::string GetName(const CmdNameList& NameList, int Id)
{
    return NameList.at(Id);
}

void BuildCmdFunctionList(CDummyController& Controller, CmdFunctionList& FunctionList, CmdNameList& NameList)
{
    // assumes list is empty?
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.BoolCommand1(Item.s_BoolValue);}  );
    NameList.push_back("DummyController/BoolCmd1");
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.BoolCommand2(Item.s_BoolValue);}  );
    NameList.push_back("DummyController/BoolCmd2");
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.IntCommand1(Item.s_IntValue);}  );
    NameList.push_back("DummyController/IntCmd1");
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.IntCommand2(Item.s_IntValue);}  );
    NameList.push_back("DummyController/IntCmd2");
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.FloatCommand1(Item.s_FloatValue);}  );
    NameList.push_back("DummyController/FloatCmd1");
    FunctionList.push_back([&Controller](const SCmdStackItem& Item){ Controller.FloatCommand2(Item.s_FloatValue);}  );
    NameList.push_back("DummyController/FloatCmd2");
}

void TestCmdFunctionList(const CmdFunctionList& FunctionList, const SCmdStackItem& Item)
{
    for(auto& Function : FunctionList)
    {
        Function(Item);
    }
}

void ExportCurrent(const CmdStack& Current, const CmdNameList& NameList)
{
    for(auto& Item : Current)
    {
        std::cout << "Exporting: Name=" << NameList.at(Item.s_Id)
                  << " BoolValue=" << Item.s_BoolValue
                  << " IntValue=" << Item.s_IntValue
                  << " FloatValue=" << Item.s_FloatValue
                  << " (internal Id=" << Item.s_Id << ")"
                  << std::endl;
    }
}

void ExtractCurrent(const CmdStack& Stack, int NumFunctionIds, CmdStack& Current)
{
    Current.assign(NumFunctionIds, SCmdStackItem());
    for(auto& Item : Stack)
    {
        Current.at(Item.s_Id) = Item;
    }
}

int main()
{
    cout << "Hello World!" << endl;


    CDummyController Controller;
    CmdFunctionList FunctionList;
    CmdNameList NameList;
    BuildCmdFunctionList(Controller, FunctionList, NameList);

    std::cout << "Testing CmdFunction list " << std::endl;
    TestCmdFunctionList(FunctionList, { 0, true, 2, 3.0f});

    CmdStack Stack;
    Stack.push_back({ 0, true, 2, 3.0f});
    Stack.push_back({ 0, false, 2, 3.0f});
    Stack.push_back({ 1, true, 2, 3.0f});
    Stack.push_back({ 1, false, 2, 3.0f});
    Stack.push_back({ 2, true, 2, 3.0f});
    Stack.push_back({ 2, true, -2, 3.0f});
    Stack.push_back({ 3, true, 2, 3.0f});
    Stack.push_back({ 3, true, -2, 3.0f});
    Stack.push_back({ 4, true, 2, 3.0f});
    Stack.push_back({ 4, true, 2, -3.0f});
    Stack.push_back({ 5, true, 2, 3.0f});
    Stack.push_back({ 5, true, 2, -3.0f});

    CmdStack Current;
    ExtractCurrent(Stack, FunctionList.size(), Current);

    std::cout << "Executing Cmd stack" << std::endl;
    ExecuteCmdStack(Stack, FunctionList);

    std::cout << "Exporting current Cmd stack" << std::endl;
    ExportCurrent(Current, NameList);

//    std::cout << "Executing current Cmd stack" << std::endl;
//    ExecuteCmdStack(Current, FunctionList);

    return 0;
}

