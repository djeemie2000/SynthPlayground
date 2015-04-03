#ifndef TOGGLEGATE_H
#define TOGGLEGATE_H

#include "Trigger.h"

template<class T>
class CToggleGate
{
public:
    CToggleGate()
        : m_GateToTrigger()
        , m_TriggerIn()
        , m_Gate(0)
    {}

    T operator()(T Toggle)
    {
        if(m_TriggerIn.IsTriggerOn(m_GateToTrigger(Toggle)))
        {
            m_Gate = 1 - m_Gate;
        }
        return m_Gate;
    }

private:
    CGateToTrigger<T> m_GateToTrigger;
    CTriggerIn<T> m_TriggerIn;
    T m_Gate;
};

#endif // TOGGLEGATE_H
