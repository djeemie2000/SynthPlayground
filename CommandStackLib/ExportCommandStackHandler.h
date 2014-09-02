#ifndef EXPORTCOMMANDSTACKHANDLER_H
#define EXPORTCOMMANDSTACKHANDLER_H

#include "CommandStack.h"
#include "CommandStackHandlerI.h"
#include "ExporterI.h"

class CExportCommandStackHandler : public ICommandStackHandler, public IExporter
{
public:
    CExportCommandStackHandler();

    void Handle(const SCmdStackItem& Item) override;
    bool Export(const std::string& Path) override;

    bool ExportToString(std::string& Content);

private:
    CmdStackMap m_Current;
};

#endif // EXPORTCOMMANDSTACKHANDLER_H
