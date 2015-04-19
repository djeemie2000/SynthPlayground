#ifndef EXPORTCOMMANDSTACKHANDLER_H
#define EXPORTCOMMANDSTACKHANDLER_H

#include "CommandStack.h"
#include "CommandStackHandlerI.h"

class CExportCommandStackHandler : public ICommandStackHandler
{
public:
    CExportCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    bool ExportToFile(const std::string& Path);
    bool ExportToString(std::string& Content);

private:
    CmdStackMap m_Current;
};

#endif // EXPORTCOMMANDSTACKHANDLER_H
