#ifndef PHASEDECREASECONDITION_H
#define PHASEDECREASECONDITION_H

template<class T>
class CPhaseDecreaseCondition
{
public:
    CPhaseDecreaseCondition()
        : m_Condition(false)
        , m_PrevValue(0)
    {
    }
    bool operator()(const T& Phase)
    {
        if(Phase<m_PrevValue)
        { // flip upon phase decrease
            m_Condition = !m_Condition;
        }
        m_PrevValue = Phase;
        return m_Condition;
    }

private:
    bool m_Condition;
    T m_PrevValue;
};

#endif // PHASEDECREASECONDITION_H
