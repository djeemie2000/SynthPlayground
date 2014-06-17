#ifndef COMMANDSTACKIMPORTER_H
#define COMMANDSTACKIMPORTER_H

#include "CommandStack.h"
#include "ImporterI.h"
#include "CommandStackHandlerI.h"

class CCommandStackImporter : public IImporter
{
public:
    CCommandStackImporter(SPCommandStackHandler Handler, const CmdStack& Defaults);

    bool Import(const string &Path) override;

    bool Default() override;

private:
    SPCommandStackHandler m_Handler;
    CmdStack m_DefaultStack;
};

#endif // COMMANDSTACKIMPORTER_H
