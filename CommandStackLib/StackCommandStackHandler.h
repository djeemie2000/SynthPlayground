#pragma once

#include <memory>
#include "CommandStackItem.h"
#include "CommandStackHandlerI.h"

class CCommandStack;

class CStackCommandStackHandler : public ICommandStackHandler
{
public:
    explicit CStackCommandStackHandler(std::shared_ptr<CCommandStack> CommandStack);

    void Handle(const SCmdStackItem& Item) override;

private:
    std::shared_ptr<CCommandStack> m_CommandStack;
};
