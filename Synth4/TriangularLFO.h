#ifndef TRIANGULARLFO_H
#define TRIANGULARLFO_H

template<class T>
class CTriangularLFO
{
public:
    CTriangularLFO()
        : m_Multiplier(1)
        , m_Phase(0)
    {}

    void SetMultiplier(const T& Multiplier)
    {
        m_Multiplier = Multiplier;
    }

    // TODO min, max => if == then fixed value at min==max

    T operator ()(const T& DeltaPhase)
    {
        m_Phase += m_Multiplier*DeltaPhase;
        if(m_Phase<0 || 1<=m_Phase)
        {
            m_Multiplier = -m_Multiplier;
            m_Phase += m_Multiplier*DeltaPhase;
        }
        return m_Phase;
    }

private:
    T m_Multiplier;
    T m_Phase;
};

#endif // TRIANGULARLFO_H
