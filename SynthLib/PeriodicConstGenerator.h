#ifndef PERIODICCONSTGENERATOR_H
#define PERIODICCONSTGENERATOR_H

#include <array>

template<class T, int N>
class CPeriodicConstGenerator
{
public:
    CPeriodicConstGenerator()
        : m_Values()
        , m_ValueIndex(0)
        , m_Period(1)
        , m_CurrentValue(0)
        , m_Counter(0)
    {
        m_Values.fill(0);
    }

    void SetPeriod(int Period)
    {
        m_Period = Period;
        m_Counter = 0;
    }

    void SetValue(int Index, T Value)
    {
        if(0<=Index && Index<N)
        {
            m_Values[Index] = Value;
        }
    }

    T operator()()
    {
        ++m_Counter;
        if(m_Period<=m_Counter)
        {
            m_ValueIndex = (m_ValueIndex+1)%N;
            m_CurrentValue = m_Values[m_ValueIndex];
            m_Counter = 0;
        }
        return m_CurrentValue;
    }

private:
    std::array<T, N> m_Values;
    int m_ValueIndex;
    int m_Period;
    T m_CurrentValue;
    int m_Counter;
};

#endif // PERIODICCONSTGENERATOR_H
