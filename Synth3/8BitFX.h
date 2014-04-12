#ifndef _8BITFX_H
#define _8BITFX_H

#include <inttypes.h>

template<class T>
class CBitCrusher
{
public:
    CBitCrusher(){}

    T operator()(T In, int N)
    {
        return In >> N << N;
    }
};

template<class T>
class CSampleAndHold
{
public:
    CSampleAndHold()
        : m_Period(0)
        , m_Cntr(0)
        , m_Sampled(0)
    {
    }

    void SetPeriod(int Period)
    {
        m_Period = Period;
        m_Cntr = Period;
    }

    T operator()(T In)
    {
        ++m_Cntr;
        if(m_Period<m_Cntr)
        {
            m_Sampled = In;
            m_Cntr = 0;
        }
        return m_Sampled;
    }
private:
    int m_Period;
    int m_Cntr;
    T m_Sampled;
};

template<class T>
class CLimiter
{
public:
    CLimiter(T Min, T Max)
        : m_Min(Min)
        , m_Max(Max)
        , m_MinTh(Min)
        , m_MaxTh(Max)
    {
    }

    void SetThreshold(T Threshold)
    {
        m_MinTh = m_Min + Threshold;
        m_MaxTh = m_Max - Threshold;
    }

    T operator()(T In)
    {
        return std::max(m_MinTh, std::min(m_MaxTh, In));
    }

private:
    T m_Min;
    T m_Max;
    T m_MinTh;
    T m_MaxTh;
    T m_Strength;
};

template<class T>
class CRippler
{
public:
    CRippler(T Min, T Max)
     : m_Min(Min)
     , m_Max(Max)
     , m_MinTh(Min)
     , m_MaxTh(Max)
     , m_Strength(0)
     , m_Ripple(0)
     , m_CurrentStrength(0)
     , m_StrengthJump(0)
    {
    }

    void SetThreshold(T Threshold)
    {
        m_MaxTh = m_Max - Threshold;
        m_MinTh = m_Min + Threshold;
    }

    void SetStrengthJump(T Jump)
    {
        m_StrengthJump = Jump;
    }

    void SetStrength(T Strength)
    {
        m_Strength = Strength;
        m_Ripple = Strength;
        m_CurrentStrength = Strength;
    }

    T operator()(T In)
    {
        //m_Ripple = 0<m_Ripple ? m_Ripple-1 : m_Strength;
        if(m_Ripple)
        {
            --m_Ripple;
        }
        else
        {
            m_CurrentStrength = (m_CurrentStrength+m_StrengthJump)%(m_Strength+1);
            m_Ripple = m_CurrentStrength;
        }

        return In<(m_Max+m_Min)/2 ? In + m_Ripple : In - m_Ripple;
    }

private:
    const T m_Min;
    const T m_Max;
    T m_MinTh;
    T m_MaxTh;
    T m_Strength;
    T m_Ripple;
    T m_CurrentStrength;
    T m_StrengthJump;
};


class C8BitFX
{
public:
    C8BitFX()
     : m_Crusher()
     , m_BitCrusherDepth(0)
     , m_SnH()
     , m_Rippler(0, 255)
    {
    }

    void SetBitCrusherDepth(int Depth)
    {
        m_BitCrusherDepth = Depth;
    }

    void SetSampleAndHoldPeriod(int Period)
    {
        m_SnH.SetPeriod(Period);
    }

    void SetRipplerStrengthJump(int Jump)
    {
        m_Rippler.SetStrengthJump(Jump);
    }

    void SetRipplerStrength(int Strength)
    {
        m_Rippler.SetStrength(Strength);
    }

    std::uint8_t operator()(std::uint8_t In)
    {
        return m_Crusher(m_SnH(m_Rippler(In)), m_BitCrusherDepth);//TODO
    }
private:
    CBitCrusher<std::uint8_t>   m_Crusher;
    int                         m_BitCrusherDepth;
    CSampleAndHold<std::uint8_t> m_SnH;
    CRippler<std::uint8_t>      m_Rippler;
    //CLimiter<std::uint8_t>  m_Rippler;
};

#endif // _8BITFX_H
