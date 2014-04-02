#ifndef PHASEGENERATOR_H
#define PHASEGENERATOR_H

template<class T>
class CPhaseGenerator
{
public:
    CPhaseGenerator()
        : m_Phase(0)
    {
    }

    void Set(const T& Phase)
    {
        m_Phase = Phase;
    }

    T operator()(const T& PhaseStep)
    {
        m_Phase += PhaseStep;
        if(1 < m_Phase)
        {
            m_Phase -= 1;
        }
        return m_Phase;
    }


private:
    T m_Phase;
};

template<class T>
class CPhaseAdder
{
public:
    CPhaseAdder(){}

    T operator()(const T& Phase, const T& AddedPhase)
    {
        T Ph = Phase + AddedPhase;
        return Ph<1 ? Ph : Ph-1;
    }
};

#endif // PHASEGENERATOR_H
