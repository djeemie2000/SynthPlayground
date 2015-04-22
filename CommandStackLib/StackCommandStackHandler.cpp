#include "StackCommandStackHandler.h"
#include "CommandStack.h"

CStackCommandStackHandler::CStackCommandStackHandler(std::shared_ptr<CCommandStack> CommandStack)
 : m_CommandStack(CommandStack)
{
}

void CStackCommandStackHandler::Handle(const SCmdStackItem& Item)
{
    if(m_CommandStack)
    {
        m_CommandStack->AddItem(Item);
    }
}
