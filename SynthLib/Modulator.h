#ifndef MODULATOR_H
#define MODULATOR_H

#include <array>
#include "Conversions.h"

template<class T>
class CModulator
{
public:
    CModulator(){}

    T operator()(T In, T ModIn, T ModAmount) const
    {
        return HardLimitBipolar(In + ModIn*ModAmount);
    }
};

template<class T>
class CModulatorUnsigned
{
public:
    CModulatorUnsigned()
     : m_ModAmt(0)
    {}

    void SetModAmount(T ModAmt)
    {
        m_ModAmt = ModAmt;
    }

    T operator()(T In, T ModIn) const
    {
        return HardLimitUnipolar(In + ModIn*m_ModAmt);
    }

    T operator()(T In, T ModIn, T ModAmount) const
    {
        return HardLimitUnipolar(In + ModIn*ModAmount);
    }

private:
    T m_ModAmt;
};

template<class T>
class CModulatorSigned
{
public:
    CModulatorSigned()
     : m_ModAmt(0)
    {}

    void SetModAmount(T ModAmt)
    {
        m_ModAmt = ModAmt;
    }

    T operator()(T In, T ModIn) const
    {
        return HardLimitBipolar(In + ModIn*m_ModAmt);
    }

    T operator()(T In, T ModIn, T ModAmount) const
    {
        return HardLimitBipolar(In + ModIn*ModAmount);
    }

private:
    T m_ModAmt;
};


template<class T>
class CModulator8Signed
{
public:
    static constexpr int Capacity = 8;

    CModulator8Signed()
     : m_ModAmt()
    {
        m_ModAmt.fill(0);
    }

    void SetModAmount(int Index, T ModAmt)
    {
        m_ModAmt[Index] = ModAmt;
    }

    T operator()(T In, T ModIn0) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0]);
    }

    T operator()(T In, T ModIn0, T ModIn1) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2, T ModIn3) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2] + ModIn3*m_ModAmt[3]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2, T ModIn3, T ModIn4) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2] + ModIn3*m_ModAmt[3] + ModIn4*m_ModAmt[4]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2, T ModIn3, T ModIn4, T ModIn5) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2] + ModIn3*m_ModAmt[3] + ModIn4*m_ModAmt[4] + ModIn5*m_ModAmt[5]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2, T ModIn3, T ModIn4, T ModIn5, T ModIn6) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2] + ModIn3*m_ModAmt[3] + ModIn4*m_ModAmt[4] + ModIn5*m_ModAmt[5] + ModIn6*m_ModAmt[6]);
    }

    T operator()(T In, T ModIn0, T ModIn1, T ModIn2, T ModIn3, T ModIn4, T ModIn5, T ModIn6, T ModIn7) const
    {
        return HardLimitBipolar(In + ModIn0*m_ModAmt[0] + ModIn1*m_ModAmt[1] + ModIn2*m_ModAmt[2] + ModIn3*m_ModAmt[3] + ModIn4*m_ModAmt[4] + ModIn5*m_ModAmt[5] + ModIn6*m_ModAmt[6] + ModIn7*m_ModAmt[7]);
    }

private:
    std::array<T, Capacity> m_ModAmt;
};

#endif // MODULATOR_H
