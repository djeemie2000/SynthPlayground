#ifndef TRIANGULARLFO_H
#define TRIANGULARLFO_H

template<class T>
class CTriangularLFO
{
public:
    CTriangularLFO()
        : m_Multiplier(1)
        , m_Phase(0)
        , m_Min(0)
        , m_Max(1)
    {}

    void SetMultiplier(const T& Multiplier)
    {
        m_Multiplier = Multiplier;
    }

    // TODO min, max => if == then fixed value at min==max
    void SetMin(const T& Min)
    {
        m_Min = Min;
        m_Phase = std::max(Min, m_Phase);
    }

    void SetMax(const T& Max)
    {
        m_Max = Max;
        m_Phase = std::min(Max, m_Phase);
    }

    // for syncing
    void SetPhase(const T& Phase)
    {
        m_Phase = Phase;
    }

    T operator ()(const T& DeltaPhase)
    {
        m_Phase += m_Multiplier*DeltaPhase;
        if(m_Phase<m_Min || m_Max<=m_Phase)
        {
            m_Multiplier = -m_Multiplier;
            m_Phase += m_Multiplier*DeltaPhase;
        }
        return m_Phase;
    }

private:
    T m_Multiplier;
    T m_Phase;
    T m_Min;
    T m_Max;
};

#endif // TRIANGULARLFO_H
