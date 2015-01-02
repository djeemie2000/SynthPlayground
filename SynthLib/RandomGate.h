#ifndef RANDOMGATE
#define RANDOMGATE

#include <cstdint>
#include "Noise.h"
#include "Conversions.h"

template<class T>
class CRandomGate
{
public:
    CRandomGate()
        : m_RandomGenerator()
        , m_Counter(0)
        , m_Gate(0)
    {}

    void SetGateOpenCenter(T Center)
    {
        // Center should be in [0,1]
        m_GateOpenDuration.s_Center = Center;
    }

    void SetGateOpenVariation(T Variation)
    {
        // Center should be in [0,1]
        m_GateOpenDuration.s_Variation = Variation;
    }

    void SetGateOpenScale(int Scale)
    {
        m_GateOpenDuration.s_Scale = Scale;
    }

    void SetGateCloseCenter(T Center)
    {
        // Center should be in [0,1]
        m_GateCloseDuration.s_Center = Center;
    }

    void SetGateCloseVariation(T Variation)
    {
        // Center should be in [0,1]
        m_GateCloseDuration.s_Variation = Variation;
    }

    void SetGateCloseScale(int Scale)
    {
        m_GateCloseDuration.s_Scale = Scale;
    }

    void Sync()
    {
        m_Counter = 0;
    }

    T operator()()
    {
        // always generate random, to get more 'random' gate lengths
        T Random = m_RandomGenerator();
        if(0<m_Counter)
        {
            --m_Counter;
        }
        else
        {
            // toggle gate
            m_Gate = 1 - m_Gate;
            // calc new duration
            if(m_Gate)
            {
                m_Counter = m_GateOpenDuration.CalcDuration(Random);
            }
            else
            {
                m_Counter = m_GateCloseDuration.CalcDuration(Random);
            }
        }
        return m_Gate;
    }

private:
    struct SDuration
    {
        T s_Center;
        T s_Variation;
        std::uint32_t s_Scale;

        SDuration()
            : s_Center(0.5)
            , s_Variation(0)
            , s_Scale(14)
        {}
        std::uint32_t CalcDuration(T Random)
        {
            // Random is random in [-1,+1]
            // calc a duration in [0,1] interval:
            // - duration is random in [Center-Variation/2, Center+Variation/2)
            // - crop to [0,1]
            // then rescale using scale
            T Duration = HardLimitUnsigned(s_Center + Random*s_Variation/2);
            return (1<<s_Scale)*Duration;
        }
    };

    CNoise<T> m_RandomGenerator;
    std::uint32_t m_Counter;
    int m_Gate;
    SDuration m_GateOpenDuration;
    SDuration m_GateCloseDuration;
};

#endif // RANDOMGATE

