#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <cstdlib>

template<class T>
T UnsignedToSigned(T Unsigned)
{
    // [0,1] to [-0.5,0.5]
    return Unsigned - 0.5;
}

template<class T>
T SignedToUnsigned(T Signed)
{
    // [-0.5,0.5] to [0,1]
    return Signed + 0.5;
}

template<class T>
T HardLimitUnsigned(T In)
{
    if(In<0)
    {
        return 0;
    }
    if(1<In)
    {
        return 1;
    }
    return In;
}
#endif // CONVERSIONS_H
