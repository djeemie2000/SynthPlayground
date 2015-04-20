#ifndef DECAYENVELOPE_H
#define DECAYENVELOPE_H

#include "Trigger.h"

template<class T>
class CDecayEnvelope
{
public:
    CDecayEnvelope()
        : m_Envelope(1)
        , m_Multiplier(0.999)
    {
    }

    void SetDecay(T Decay)
    {
        // Decay is in ]0,1[
        // low decay => slow decay <=> multiplier closer to 1
        // high decay => fast decay <=> multiplier closer to 0
        // so the multiplier equals 1-Decay;
        if(0<Decay && Decay<1)
        {
            m_Multiplier = 1-Decay*Decay;
        }
    }

    void NoteOn()
    {
        m_Envelope = 1;
    }

    void NoteOff()
    {
        // ignored
    }

    T operator()()
    {
        m_Envelope*=m_Multiplier;
        return m_Envelope;
    }

    T operator()(T Trigger, T Decay)
    {
        T Multiplier = 1-Decay*Decay;
        m_Envelope = CTriggerIn<T>().IsTriggerOn(Trigger) ? 1 : m_Envelope*Multiplier;
        return m_Envelope;
    }

private:
    T m_Envelope;
    T m_Multiplier;
};

#endif // DECAYENVELOPE_H
