#ifndef ADSRENVELOPE_H
#define ADSRENVELOPE_H

#include <array>

template<class T>
class CADSREnvelope
{
public:
    CADSREnvelope()
        : m_Envelope(0)
        , m_Increment()
        , m_Target()
        , m_CurrentSegment(0)
    {
        // pre attack (silence)
        m_Increment[0] = 0;
        m_Target[0] = 0;
        // attack default 0
        m_Increment[1] = 1;
        m_Target[1] = 1;
        //decay default 0
        m_Increment[2] = -1;
        // default sustain is 1
        m_Target[2] = 1;
        m_Increment[3] = 0;
        m_Target[3] = 1;
        // release default 0
        m_Increment[4] = -1;
        m_Target[4] = 0;
        // post release (silence)
        m_Increment[5] = 0;
        m_Target[5] = 0;
    }

    void SetAttackSamples(T Attack)
    {
        if(0<Attack)
        {
            m_Increment[1] = 1/Attack;
        }
        else
        {
            m_Increment[1] = 1;
        }
    }

    void SetDecaySamples(T Decay)
    {
        if(0<Decay)
        {
            m_Increment[2] = -1/Decay;
        }
        else
        {
            m_Increment[2] = -1;
        }
    }

    void SetSustain(T Sustain)
    {
        m_Target[2] = Sustain;
        m_Target[3] = Sustain;
    }

    void SetReleaseSamples(T Release)
    {
        if(0<Release)
        {
            m_Increment[4] = -m_Target[3]/Release;
        }
        else
        {
            m_Increment[4] = -1;
        }
    }

    void NoteOn()
    {
        m_CurrentSegment = 1;//attack
    }

    void NoteOff()
    {
        m_CurrentSegment = 4;//release
    }

    T operator()()
    {
        if(m_Increment[m_CurrentSegment])
        {
            m_Envelope += m_Increment[m_CurrentSegment];

            if(0<m_Increment[m_CurrentSegment])
            {
                // positive increment
                if(m_Target[m_CurrentSegment]<m_Envelope)
                {
                    m_Envelope = m_Target[m_CurrentSegment];
                    // goto next segment
                    ++m_CurrentSegment;
                }
            }
            else if(m_Increment[m_CurrentSegment]<0)
            {
                // negative increment
                if(m_Envelope<m_Target[m_CurrentSegment])
                {
                    m_Envelope = m_Target[m_CurrentSegment];
                    // goto next segment
                    ++m_CurrentSegment;
                }
            }
        }
        else
        {
            m_Envelope = m_Target[m_CurrentSegment];
        }

        return m_Envelope;
    }

private:
    static const int NumSegments = 6;
    T m_Envelope;
    std::array<T, NumSegments> m_Increment;
    std::array<T, NumSegments> m_Target;
    int m_CurrentSegment;
};

#endif // ADSRENVELOPE_H
