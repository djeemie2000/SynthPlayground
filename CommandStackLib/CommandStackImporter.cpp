#include <iostream>
#include <fstream>
#include <sstream>
#include "CommandStackImporter.h"
#include "CommandStack.h"

CCommandStackImporter::CCommandStackImporter()
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

bool ImportCurrentStackFromString(CmdStack& CurrentStack, const std::string& Content)
{
    std::cout << "Importing from string " << std::endl;
    std::istringstream InFile(Content.c_str());
    return ImportCurrentStack(CurrentStack, InFile);
}

}

bool CCommandStackImporter::ImportFromString(const string &Content, ICommandStackHandler &Handler)
{
    CmdStack ImportedStack;
    if(ImportCurrentStackFromString(ImportedStack, Content))
    {
        for(auto& Item : ImportedStack)
        {
            Handler.Handle(Item);
        }
        return true;
    }
    return false;
}

bool CCommandStackImporter::ImportFromString(const string &Content, CCommandStack &CommandStack)
{
    CmdStack ImportedStack;
    if(ImportCurrentStackFromString(ImportedStack, Content))
    {
        CommandStack.Clear();
        for(auto& Item : ImportedStack)
        {
            CommandStack.AddItem(Item);
        }
        return true;
    }
    return false;
}

bool CCommandStackImporter::ImportFromString(const string &Content, const CCommandStack &DefaultCommandStack, CCommandStack &CommandStack)
{
    CmdStack ImportedStack;
    if(ImportCurrentStackFromString(ImportedStack, Content))
    {
        CommandStack.Clear();
        for(auto& ImportedItem : ImportedStack)
        {
            // use default stack because this knows the correct type
            SCmdStackItem Item = DefaultCommandStack.GetItem(ImportedItem.Name());
            Item.Name(ImportedItem.Name());// in case was not part of defaults
            // do no use BoolValue(..), ... because this will change the type
            Item.s_BoolValue = ImportedItem.s_BoolValue;
            Item.s_IntValue = ImportedItem.s_IntValue;
            Item.s_FloatValue = ImportedItem.s_FloatValue;
            CommandStack.AddItem(Item);
        }
        return true;
    }
    return false;
}
