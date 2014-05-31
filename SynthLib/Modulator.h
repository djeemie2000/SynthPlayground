#ifndef MODULATOR_H
#define MODULATOR_H

#include "Conversions.h"

template<class T>
class CModulator
{
public:
    CModulator(){}

    T operator()(T In, T ModIn, T ModAmount)
    {
        return HardLimitSigned(In + ModIn*ModAmount);
    }
};

#endif // MODULATOR_H
