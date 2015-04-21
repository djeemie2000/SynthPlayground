#pragma once

#include <string>
#include "CommandStackItem.h"

class ICommandStackHandler;

class CCommandStack
{
public:
    CCommandStack();

    void AddItem(const SCmdStackItem& Item);
    void RemoveItem(const std::string& CommandName);
    void Clear();
    SCmdStackItem GetItem(const std::string& CommandName) const;
    void Apply(ICommandStackHandler& Handler) const;

    void AddItems(const CCommandStack& OtherStack);
    CmdStack GetStack() const;// should be a visitor?

private:
    CmdStackMap m_Stack;
};
