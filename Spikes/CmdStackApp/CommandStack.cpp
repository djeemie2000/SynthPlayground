#include <iostream>
#include <fstream>
#include "CommandStack.h"

void TestCmdFunctionMap(const CmdFunctionMap& FunctionMap, const SCmdStackItem& Item)
{
    for(auto& Function : FunctionMap)
    {
        std::cout << "Testing Cmd " << Function.first << ": " << std::endl;
        Function.second(Item);
    }
}

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

void ExecuteCmdStack(CmdStack& Stack, ICommandStackHandler& Handler)
{
    for(auto& Item : Stack)
    {
        Handler.Handle(Item);
    }
}

bool ExportCurrentStack(const CmdStack& CurrentStack, const std::string& Path)
{
    std::cout << "Exporting to " << Path << std::endl;
    std::ofstream OutFile;
    OutFile.open(Path.c_str());
    if(OutFile.is_open())
    {
        for(auto& Item : CurrentStack)
        {
            std::cout << "Exporting: Name=" << Item.s_Name
                      << " BoolValue=" << Item.s_BoolValue
                      << " IntValue=" << Item.s_IntValue
                      << " FloatValue=" << Item.s_FloatValue
                      << std::endl;
            char Separator = ' ';
            OutFile << Item.s_Name << Separator
                    << Item.s_BoolValue << Separator
                    << Item.s_IntValue << Separator
                    << Item.s_FloatValue << std::endl;
        }
        return true;
    }

    std::cout << "Error: failed to open " << Path << " for writing" << std::endl;
    return false;
}

bool ImportCurrentStack(CmdStack& CurrentStack, const std::string& Path)
{
    std::cout << "Importing from " << Path << std::endl;
    std::ifstream InFile;
    InFile.open(Path.c_str());
    if(InFile.is_open())
    {
        while(!InFile.eof())
        {
            SCmdStackItem Item;
            InFile >> Item.s_Name
                    >> Item.s_BoolValue
                    >> Item.s_IntValue
                    >> Item.s_FloatValue;

            if(!InFile.eof())
            {
                CurrentStack.push_back(Item);

                std::cout << "Importing: Name=" << Item.s_Name
                          << " BoolValue=" << Item.s_BoolValue
                          << " IntValue=" << Item.s_IntValue
                          << " FloatValue=" << Item.s_FloatValue
                          << std::endl;
            }

        }
        return true;
    }

    std::cout << "Error: failed to open " << Path << " for reading" << std::endl;
    return false;
}

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


CLogCommandStackHandler::CLogCommandStackHandler()
{
}

void CLogCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    std::cout << "Handling Item " << Item.s_Name << " (" << Item.s_BoolValue << "," << Item.s_IntValue << "," << Item.s_FloatValue << ")" << std::endl;//TODO
}


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
{
}


CExportCommandStackHandler::CExportCommandStackHandler()
{
}

void CExportCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    m_Current[Item.s_Name] = Item;
}

bool CExportCommandStackHandler::Export(const string &Path)
{
    CmdStack CurrentStack;
    ExtractCurrentStack(m_Current, CurrentStack);
    return ExportCurrentStack(CurrentStack, Path);
}


CExecuteCommandStackHandler::CExecuteCommandStackHandler(const CmdFunctionMap &FunctionMap)
 : m_FunctionMap(FunctionMap)
{
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


CMultiCommandStackHandler::CMultiCommandStackHandler()
 : m_Handlers()
{
}

void CMultiCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->Handle(Item);
    }
}

void CMultiCommandStackHandler::Register(SPCommandStackHandler Handler)
{
    m_Handlers.push_back(Handler);
}


CCommandStackImporter::CCommandStackImporter(SPCommandStackHandler Handler, const CmdStack &Defaults)
 : m_Handler(Handler)
 , m_DefaultStack(Defaults)
{
}

bool CCommandStackImporter::Import(const string &Path)
{
    CmdStack ImportedStack;
    if(ImportCurrentStack(ImportedStack, Path))
    {
        for(auto& Item : ImportedStack)
        {
            m_Handler->Handle(Item);
        }
        return true;
    }
    return false;
}

bool CCommandStackImporter::Default()
{
    for(auto& Item : m_DefaultStack)
    {
        m_Handler->Handle(Item);
    }
    return true;
}


CCommandStackDistributor::CCommandStackDistributor()
    : m_Handlers()
{
}

void CCommandStackDistributor::Handle(const SCmdStackItem &Item)
{
    auto itHandler = m_Handlers.find(Item.s_Name);
    if(itHandler!=m_Handlers.end())
    {
        itHandler->second->Handle(Item);
    }
}

void CCommandStackDistributor::Register(const string &Name, SPCommandStackHandler Handler)
{
    m_Handlers[Name] = Handler;
}
