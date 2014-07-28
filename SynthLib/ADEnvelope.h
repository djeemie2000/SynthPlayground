#ifndef ADENVELOPE_H
#define ADENVELOPE_H

template<class T>
class CADEnvelope
{
public:
    CADEnvelope()
        : m_Envelope(0)
        , m_Increment(0)
        , m_AttackIncrement(1)
        , m_DecayIncrement(-1)
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

    void SetDecaySamples(T Decay)
    {
        if(0<Decay)
        {
            m_DecayIncrement = -1/Decay;
        }
        else
        {
            m_DecayIncrement = -1;
        }
    }

    void NoteOn()
    {
        m_Envelope = 0;
        m_Increment = m_AttackIncrement;
    }

    void NoteOff()
    {
        // goto silence
        m_Increment = 0;
        m_Envelope = 0;
    }


    T operator()()
    {
        if(m_Increment)
        {
            m_Envelope += m_Increment;

            if(0<m_Increment)
            { // positive increment
                if(1<m_Envelope)
                {
                    // goto decay phase
                    m_Increment = m_DecayIncrement;
                    m_Envelope = 1;
                }
            }
            else
            { // negative increment
                if(m_Envelope<0)
                {// goto silence
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
    T m_DecayIncrement;
};


#endif // ADENVELOPE_H
