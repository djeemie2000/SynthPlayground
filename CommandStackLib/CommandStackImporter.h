#ifndef COMMANDSTACKIMPORTER_H
#define COMMANDSTACKIMPORTER_H

#include <string>
#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"

class CCommandStack;

class CCommandStackImporter
{
public:
    CCommandStackImporter();

    bool ImportFromString(const std::string& Content, ICommandStackHandler& Handler);
    bool ImportFromString(const std::string& Content, CCommandStack& CommandStack);
};

#endif // COMMANDSTACKIMPORTER_H
