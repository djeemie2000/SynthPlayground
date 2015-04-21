#include "CommandStack.h"
#include "CommandStackHandlerI.h"



CCommandStack::CCommandStack()
 : m_Stack()
{
}

void CCommandStack::AddItem(const SCmdStackItem &Item)
{
    // add or overwrite
    m_Stack[Item.s_Name] = Item;
}

void CCommandStack::RemoveItem(const string &CommandName)
{
    m_Stack.erase(CommandName);
}

void CCommandStack::Clear()
{
    m_Stack.clear();
}

SCmdStackItem CCommandStack::GetItem(const string &CommandName) const
{
    auto itItem = m_Stack.find(CommandName);
    return (itItem == m_Stack.end()) ? itItem->second : SCmdStackItem();
}

void CCommandStack::Apply(ICommandStackHandler &Handler) const
{
    for(const auto& Item : m_Stack)
    {
        Handler.Handle(Item.second);
    }
}

void CCommandStack::AddItems(const CCommandStack &OtherStack)
{
    for(const auto& Item : OtherStack.m_Stack)
    {
        AddItem(Item.second);
    }
}

CmdStack CCommandStack::GetStack() const
{
    CmdStack Stack;
    for(auto& Item : m_Stack)
    {
        Stack.push_back(Item.second);
    }
    return Stack;
}
