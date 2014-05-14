#ifndef PERIODICTICKER_H
#define PERIODICTICKER_H

class CPeriodicTicker
{
public:
    CPeriodicTicker()
        : m_Period(64)
        , m_Counter(m_Period)
        , m_IsActive(false)
    {}

    void Activate(bool Active)
    {
        m_IsActive = Active;
    }

    void SetPeriod(int Period)
    {
        m_Period = Period-1;
        m_Counter = 1;
    }

    bool operator()()
    {
        m_Counter = 0<m_Counter ? m_Counter-1 : m_Period;
        return !m_Counter && m_IsActive;
    }

private:
    int m_Period;
    int m_Counter;
    bool m_IsActive;
};

#endif // PERIODICTICKER_H
