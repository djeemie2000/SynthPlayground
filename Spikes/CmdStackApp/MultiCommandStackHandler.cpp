#include "MultiCommandStackHandler.h"

CMultiCommandStackHandler::CMultiCommandStackHandler()
 : m_Handlers()
{
}

void CMultiCommandStackHandler::Handle(const SCmdStackItem &Item)
{
    for(auto& Handler : m_Handlers)
    {
        Handler->Handle(Item);
    }
}

void CMultiCommandStackHandler::Register(SPCommandStackHandler Handler)
{
    m_Handlers.push_back(Handler);
}
