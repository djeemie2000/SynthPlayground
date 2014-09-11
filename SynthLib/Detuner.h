#ifndef DETUNER_H
#define DETUNER_H

#include <cmath>

template<class T>
class CDetuner
{
public:
    CDetuner()
     : m_OctaveMultiplier(1)
     , m_DetuneMultiplier(1)
    {
    }

    void SetDetune(T Detune)
    {
        // will use logaritmic scale i.e.
        // Detune = 0 corresponds to * 1.0
        // Detune = 1 corresponds to * 2.0
        // Detune = -1 corresponds to * 0.5
        // ...
        m_DetuneMultiplier = std::pow(2, Detune);
    }

    void SetOctaveShift(int OctaveShift)
    {
        // OctaveShift = 0 corresponds to * 1.0
        // OctaveShift = +1 corresponds to * 2.0
        // OctaveShift = +2 corresponds to * 4.0
        // OctaveShift = -1 corresponds to * 0.5
        // OctaveShift = -2 corresponds to * 0.25
        m_OctaveMultiplier = std::pow(2, OctaveShift);
    }

    T operator()(T Frequency)
    {
        return m_OctaveMultiplier*m_DetuneMultiplier*Frequency;
    }


private:
    T m_OctaveMultiplier;
    T m_DetuneMultiplier;
};


#endif // DETUNER_H
