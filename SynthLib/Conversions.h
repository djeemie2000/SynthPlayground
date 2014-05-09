#ifndef CONVERSIONS_H
#define CONVERSIONS_H

//#include <cstdlib>
#include <cstdint>

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

template<class T>
T HardLimitSigned(T In)
{
    if(In<-1)
    {
        return -1;
    }
    if(1<In)
    {
        return 1;
    }
    return In;
}

template<class T>
T SignedFullToUnsigned(T In)
{
    // [-1,+1] to [0,1]
    return (1 + In) / 2;
}

//template<class To, class From>
//To SignedToInteger(From /*In*/)
//{
//    return 0;
//}

template<class From>
std::uint8_t SignedToUint8(From In)
{
    return 128+127*In;//SignedFullToUnsigned(In)*255;
}

template<class From>
std::int16_t SignedToInt16(From In)
{
    return In*32767;
}



#endif // CONVERSIONS_H
