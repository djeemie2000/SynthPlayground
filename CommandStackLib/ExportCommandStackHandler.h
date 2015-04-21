#ifndef EXPORTCOMMANDSTACKHANDLER_H
#define EXPORTCOMMANDSTACKHANDLER_H

#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"

class CExportCommandStackHandler : public ICommandStackHandler
{
public:
    CExportCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;

    bool ExportToString(std::string& Content);

private:
    CmdStackMap m_Current;
};

#endif // EXPORTCOMMANDSTACKHANDLER_H
