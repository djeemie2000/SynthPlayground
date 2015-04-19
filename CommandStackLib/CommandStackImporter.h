#ifndef COMMANDSTACKIMPORTER_H
#define COMMANDSTACKIMPORTER_H

#include <string>
#include "CommandStack.h"
#include "CommandStackHandlerI.h"

class CCommandStackImporter
{
public:
    CCommandStackImporter(SPCommandStackHandler Handler, const CmdStack& Defaults);

    bool Import(const std::string &Path);
    bool Default();

    void AddDefault(const SCmdStackItem& Default);
    void RemoveDefault(const std::string& CommandName);
    bool ImportFromString(const std::string& Content);

private:
    SPCommandStackHandler m_Handler;
    CmdStack m_DefaultStack;
};

#endif // COMMANDSTACKIMPORTER_H
