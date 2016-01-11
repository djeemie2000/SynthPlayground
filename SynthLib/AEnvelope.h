#ifndef AENVELOPE_H
#define AENVELOPE_H

template<class T>
class CAEnvelope
{
public:
    CAEnvelope()
        : m_Envelope(0)
        , m_Increment(0)
        , m_AttackIncrement(1)
    {}

    void SetAttackSamples(T Attack)
    {
        if(0<Attack)
        {
            m_AttackIncrement = 1/Attack;
        }
        else
        {
            m_AttackIncrement = 1;
        }
    }

    void NoteOn()
    {
        m_Envelope = 0;
        m_Increment = m_AttackIncrement;
    }

    void NoteOff()
    {
    }

    T operator()()
    {
        if(m_Increment)
        {
            m_Envelope += m_Increment;

            if(1<m_Envelope)
            {
                // goto sustain phase at 1
                m_Increment = 0;
                m_Envelope = 1;
            }

        }

        return m_Envelope;
    }

private:
    T m_Envelope;
    T m_Increment;
    T m_AttackIncrement;
};

#endif // AENVELOPE_H
