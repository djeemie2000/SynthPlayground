#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <cstdint>
#include <vector>

template<class T>
T HardLimitUnipolar(T In)
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
T HardLimitBipolar(T In)
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
void CropSigned(T& In)
{
    if(In<-1)
    {
        In = -1;
    }
    else if(1<In)
    {
        In = 1;
    }
}

template<class T>
void CropUnsigned(T& In)
{
    if(In<0)
    {
        In = 0;
    }
    else if(1<In)
    {
        In = 1;
    }
}

template<class T>
T BipolarToUnipolar(T In)
{
    // [-1,+1] to [0,1]
    return (1 + In) / 2;
}

template<class T>
T UnipolarToBipolar(T In)
{
    // [0,1] to [-1,+1]
    return 2*In -1;
}

template<class From>
std::uint8_t SignedToUint8(From In)
{
    return 128+127*In;
}

template<class From>
std::int16_t SignedToInt16(From In)
{
    return In*INT16_MAX;
}

template<class T>
void SplitStereo(const std::vector<T>& Stereo, std::vector<T>& Left, std::vector<T>& Right)
{
    Left.assign(Stereo.size()/2, 0);
    Right.assign(Stereo.size()/2, 0);
    for(int idx = 0; idx<Stereo.size()/2; ++idx)
    {
        Left[idx] = Stereo[2*idx];
        Right[idx] = Stereo[2*idx+1];
    }
}

#endif // CONVERSIONS_H
