#ifndef ASRENVELOPE_H
#define ASRENVELOPE_H

template<class T>
class CASREnvelope
{
public:
    CASREnvelope()
        : m_Envelope(0)
        , m_Increment(0)
        , m_AttackIncrement(1)
        , m_Sustain(1)
        , m_ReleaseIncrement(-1)
    {}

    void SetAttackSamples(T Attack)
    {
        if(0<Attack)
        {
            m_AttackIncrement = m_Sustain/Attack;
        }
        else
        {
            m_AttackIncrement = m_Sustain;
        }
    }

    void SetReleaseSamples(T Release)
    {
        if(0<Release)
        {
            m_ReleaseIncrement = -m_Sustain/Release;
        }
        else
        {
            m_ReleaseIncrement = -m_Sustain;
        }
    }

    void SetSustain(T Sustain)
    {
        if(0<=Sustain && Sustain<=1)
        {
            m_Sustain = Sustain;
        }
    }

    void NoteOn()
    {
        m_Envelope = 0;
        m_Increment = m_AttackIncrement;
    }

    void NoteOff()
    {
        m_Increment = m_ReleaseIncrement;
    }

    T operator()()
    {
        if(m_Increment)
        {
            m_Envelope += m_Increment;

            if(0<m_Increment)
            { // positive increment : attack
                if(m_Sustain<m_Envelope)
                {
                    m_Increment = 0;
                    m_Envelope = m_Sustain;
                }
            }
            else
            { // negative increment : release
                if(m_Envelope<0)
                {
                    m_Increment = 0;
                    m_Envelope = 0;
                }
            }
        }

        return m_Envelope;
    }

private:
    T m_Envelope;
    T m_Increment;
    T m_AttackIncrement;
    T m_Sustain;
    T m_ReleaseIncrement;
};

#endif // ASRENVELOPE_H
