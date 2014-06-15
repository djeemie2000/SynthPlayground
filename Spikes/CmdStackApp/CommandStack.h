#ifndef COMMANDSTACK_H
#define COMMANDSTACK_H

#include <iostream>
#include <deque>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <memory>

using namespace std;

struct SCmdStackItem
{
    std::string s_Name;
    bool s_BoolValue;
    int s_IntValue;
    float s_FloatValue;

    SCmdStackItem();

    SCmdStackItem(const std::string& Name, bool BoolValue, int IntValue, float FloatValue);
};

typedef std::deque<SCmdStackItem> CmdStack;

class ICommandStackHandler
{
public:
    virtual ~ICommandStackHandler(){}

    virtual void Handle(const SCmdStackItem& Item) =0;
};

typedef std::shared_ptr<ICommandStackHandler> SPCommandStackHandler;

class CLogCommandStackHandler : public ICommandStackHandler
{
public:
    CLogCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

};

typedef std::function<void(const SCmdStackItem&)> CmdFunction;
typedef std::map<std::string, CmdFunction> CmdFunctionMap;

void ExecuteCmdStack(CmdStack& Stack, ICommandStackHandler &Handler);

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

    void Command1()
    {
        std::cout << "Command1 (no value)" << std::endl;
    }

};

void BuildCmdFunctionMap(CDummyController& Controller, CmdFunctionMap& FunctionMap);
void TestCmdFunctionMap(const CmdFunctionMap& FunctionMap, const SCmdStackItem& Item);

typedef std::map<std::string, SCmdStackItem> CmdStackMap;

void UpdateCurrent(const CmdStack& Stack, CmdStackMap& Current);
void ExtractCurrentStack(const CmdStackMap& Current, CmdStack& CurrentStack);

bool ExportCurrentStack(const CmdStack& CurrentStack, const string &Path);

class IExporter
{
public:
    virtual ~IExporter(){}

    virtual bool Export(const std::string& Path) =0;
};

class CExportCommandStackHandler : public ICommandStackHandler, public IExporter
{
public:
    CExportCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    bool Export(const std::string& Path) override;

private:
    CmdStackMap m_Current;
};

class IImporter
{
public:
    virtual ~IImporter(){}

    virtual bool Import(const std::string& Path) =0;
};

class CCommandStackImporter : public IImporter
{
public:
    CCommandStackImporter(SPCommandStackHandler Handler);

    bool Import(const string &Path) override;

private:
    SPCommandStackHandler m_Handler;
};

class CExecuteCommandStackHandler : public ICommandStackHandler
{
public:
    CExecuteCommandStackHandler(const CmdFunctionMap& FunctionMap);

    void Handle(const SCmdStackItem& Item) override;

    void Add(const std::string& Name, const CmdFunction& Function);

private:
    CmdFunctionMap m_FunctionMap;
};

class CMultiCommandStackHandler : public ICommandStackHandler
{
public:
    CMultiCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    void Register(SPCommandStackHandler Handler);

private:
    typedef std::vector<SPCommandStackHandler> HandlerList;
    HandlerList m_Handlers;
};

class IRegisterNamedCommandStackHandler
{
public:
    virtual ~IRegisterNamedCommandStackHandler(){}

    virtual void Register(const std::string& Name, SPCommandStackHandler Handler) =0;
};

class CCommandStackDistributor : public ICommandStackHandler, public IRegisterNamedCommandStackHandler
{
public:
    CCommandStackDistributor();

    void Handle(const SCmdStackItem &Item) override;

    void Register(const std::string& Name, SPCommandStackHandler Handler) override;

private:
    typedef std::map<std::string, SPCommandStackHandler> HandlerMap;
    HandlerMap m_Handlers;
};

#endif // COMMANDSTACK_H
