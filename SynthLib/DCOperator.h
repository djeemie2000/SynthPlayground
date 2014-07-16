#ifndef DCOPERATOR_H
#define DCOPERATOR_H

#include <cmath>
#include "Conversions.h"

template<class T>
class CFixedGainDCOperator
{
public:
    CFixedGainDCOperator()
        : m_PreGain(1)
    {}

    void SetPreGain(T PreGain)
    {
        m_PreGain = PreGain;
    }

    T operator()(T In, T DCOffset)
    {
        return HardLimitSigned(m_PreGain*In+DCOffset);
    }

private:
    T m_PreGain;
};

template<class T>
class CAutoGainDCOperator
{
public:
    CAutoGainDCOperator()
    {}

    T operator()(T In, T DCOffset)
    {
        // make sure to stay within limits [-1,+1]
        // by multiplying In [-1,+1] with pre gain 1-abs(Offset)
        // before applying offset
        T PreGain = 1-std::abs(DCOffset);
        return PreGain*In+DCOffset;
    }

};

#endif // DCOPERATOR_H
