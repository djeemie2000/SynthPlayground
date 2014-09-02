#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CommandStackImporter.h"

CCommandStackImporter::CCommandStackImporter(SPCommandStackHandler Handler, const CmdStack &Defaults)
 : m_Handler(Handler)
 , m_DefaultStack(Defaults)
{
}

namespace
{

bool ImportCurrentStack(CmdStack& CurrentStack, std::istream& InFile)
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

bool ImportCurrentStack(CmdStack& CurrentStack, const std::string& Path)
{
    std::cout << "Importing from " << Path << std::endl;
    std::ifstream InFile;
    InFile.open(Path.c_str());
    if(InFile.is_open())
    {
        return ImportCurrentStack(CurrentStack, InFile);
//        while(!InFile.eof())
//        {
//            SCmdStackItem Item;
//            InFile >> Item.s_Name
//                    >> Item.s_BoolValue
//                    >> Item.s_IntValue
//                    >> Item.s_FloatValue;

//            if(!InFile.eof())
//            {
//                CurrentStack.push_back(Item);

//                std::cout << "Importing: Name=" << Item.s_Name
//                          << " BoolValue=" << Item.s_BoolValue
//                          << " IntValue=" << Item.s_IntValue
//                          << " FloatValue=" << Item.s_FloatValue
//                          << std::endl;
//            }

//        }
//        return true;
    }

    std::cout << "Error: failed to open " << Path << " for reading" << std::endl;
    return false;
}

bool ImportCurrentStackFromString(CmdStack& CurrentStack, const std::string& Content)
{
    std::cout << "Importing from string " << std::endl;
    std::istringstream InFile(Content.c_str());
    return ImportCurrentStack(CurrentStack, InFile);
}

}

bool CCommandStackImporter::Import(const std::string &Path)
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

void CCommandStackImporter::AddDefault(const SCmdStackItem &Default)
{
    m_DefaultStack.push_back(Default);
}

void CCommandStackImporter::RemoveDefault(const string &CommandName)
{
    auto itDefault = std::find_if(m_DefaultStack.begin(),
                                  m_DefaultStack.end(),
                                  [&CommandName](const SCmdStackItem& Item){ return Item.s_Name == CommandName; });
    if(itDefault != m_DefaultStack.end())
    {
        m_DefaultStack.erase(itDefault);
    }
}

bool CCommandStackImporter::ImportFromString(const string &Content)
{
    CmdStack ImportedStack;
    if(ImportCurrentStackFromString(ImportedStack, Content))
    {
        for(auto& Item : ImportedStack)
        {
            m_Handler->Handle(Item);
        }
        return true;
    }
    return false;
}
