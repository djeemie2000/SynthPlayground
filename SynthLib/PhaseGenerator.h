#ifndef PHASEGENERATOR_H
#define PHASEGENERATOR_H

template<class T>
class CPhaseGenerator
{
public:
    static constexpr T MinPhase = static_cast<T>(-1);
    static constexpr T MaxPhase = static_cast<T>(1);
    static constexpr T PhaseRange = MaxPhase - MinPhase;

    CPhaseGenerator()
        : m_Phase(0)
    {
    }

    void Set(const T& Phase)
    {
        m_Phase = Phase;
    }

    void Sync()
    {
        m_Phase = MinPhase;
    }

    void Sync(T Phase)
    {
        m_Phase = MinPhase + Phase;
    }

    T operator()(const T& PhaseStep)
    {
        m_Phase += PhaseStep;
        if(MaxPhase < m_Phase)
        {
            m_Phase -= PhaseRange;
        }
        return m_Phase;
    }


private:
    T m_Phase;
};


#endif // PHASEGENERATOR_H
