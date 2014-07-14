#ifndef MODULATOR_H
#define MODULATOR_H

#include "Conversions.h"

template<class T>
class CModulator
{
public:
    CModulator(){}

    T operator()(T In, T ModIn, T ModAmount) const
    {
        return HardLimitSigned(In + ModIn*ModAmount);
    }
};

template<class T>
class CModulatorUnsigned
{
public:
    CModulatorUnsigned()
     : m_ModAmt(0)
    {}

    void SeTModAmount(T ModAmt)
    {
        m_ModAmt = ModAmt;
    }

    T operator()(T In, T ModIn) const
    {
        return HardLimitUnsigned(In + ModIn*m_ModAmt);
    }

    T operator()(T In, T ModIn, T ModAmount) const
    {
        return HardLimitUnsigned(In + ModIn*ModAmount);
    }

private:
    T m_ModAmt;
};

#endif // MODULATOR_H
