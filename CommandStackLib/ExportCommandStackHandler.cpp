#include <iostream>
#include <fstream>
#include <sstream>
#include "ExportCommandStackHandler.h"

CExportCommandStackHandler::CExportCommandStackHandler()
{
}

void CExportCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    m_Current[Item.s_Name] = Item;
}

namespace
{

void ExtractCurrentStack(const CmdStackMap& Current, CmdStack& CurrentStack)
{
    for(auto& Item : Current)
    {
        CurrentStack.push_back(Item.second);
    }
}

bool ExportCurrentStack(const CmdStack& CurrentStack, std::ostream& OutFile)
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

bool ExportCurrentStack(const CmdStack& CurrentStack, const std::string& Path)
{
    std::cout << "Exporting to " << Path << std::endl;
    std::ofstream OutFile;
    OutFile.open(Path.c_str());
    if(OutFile.is_open())
    {
        return ExportCurrentStack(CurrentStack, OutFile);
//        for(auto& Item : CurrentStack)
//        {
//            std::cout << "Exporting: Name=" << Item.s_Name
//                      << " BoolValue=" << Item.s_BoolValue
//                      << " IntValue=" << Item.s_IntValue
//                      << " FloatValue=" << Item.s_FloatValue
//                      << std::endl;
//            char Separator = ' ';
//            OutFile << Item.s_Name << Separator
//                    << Item.s_BoolValue << Separator
//                    << Item.s_IntValue << Separator
//                    << Item.s_FloatValue << std::endl;
//        }
//        return true;
    }

    std::cout << "Error: failed to open " << Path << " for writing" << std::endl;
    return false;
}

bool ExportCurrentStackToString(const CmdStack& CurrentStack, std::string& Content)
{
    std::cout << "Exporting to string " << std::endl;
    std::ostringstream OutFile;
    if(ExportCurrentStack(CurrentStack, OutFile))
    {
        Content = OutFile.str();
        return true;
    }

    return false;
}

}

bool CExportCommandStackHandler::Export(const string &Path)
{
    CmdStack CurrentStack;
    ExtractCurrentStack(m_Current, CurrentStack);
    return ExportCurrentStack(CurrentStack, Path);
}

bool CExportCommandStackHandler::ExportToString(string &Content)
{
    CmdStack CurrentStack;
    ExtractCurrentStack(m_Current, CurrentStack);
    return ExportCurrentStackToString(CurrentStack, Content);
}
