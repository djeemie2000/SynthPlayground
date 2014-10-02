#ifndef ENVELOPEFOLLOWER_H
#define ENVELOPEFOLLOWER_H

#include <cmath>


template<class T>
class CEnvelopeFollower
{
public:
    CEnvelopeFollower(T SamplingFrequency)
     : m_SamplingFrequency(SamplingFrequency)
     , m_Attack(0)
     , m_Release(0)
     , m_Envelope(0)
    {
        SetAttack(1);
        SetRelease(1);
    }

    void SetAttack(T AttackMilliSeconds)
    {
        m_Attack = std::pow( 0.01, 1.0 / ( AttackMilliSeconds * m_SamplingFrequency * 0.001 ) );
    }

    void SetRelease(T ReleaseMilliSeconds)
    {
        m_Release = std::pow( 0.01, 1.0 / ( ReleaseMilliSeconds * m_SamplingFrequency * 0.001 ) );
    }

    void Reset()
    {
        m_Envelope = 0;
    }

    T operator()(T In)
    {
        T Temp = std::abs(In);
        m_Envelope = (m_Envelope<Temp) ? (m_Attack*(m_Envelope - Temp) + Temp) : (m_Release*(m_Envelope - Temp) + Temp);
        return m_Envelope;
    }

private:
    T m_SamplingFrequency;
    T m_Attack;
    T m_Release;
    T m_Envelope;
};

#endif // ENVELOPEFOLLOWER_H
