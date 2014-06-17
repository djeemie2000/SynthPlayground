#include "CommandStackDistributor.h"

CCommandStackDistributor::CCommandStackDistributor()
    : m_Handlers()
{
}

void CCommandStackDistributor::Handle(const SCmdStackItem &Item)
{
    auto itHandler = m_Handlers.find(Item.s_Name);
    if(itHandler!=m_Handlers.end())
    {
        itHandler->second->Handle(Item);
    }
}

void CCommandStackDistributor::Register(const string &Name, SPCommandStackHandler Handler)
{
    m_Handlers[Name] = Handler;
}
