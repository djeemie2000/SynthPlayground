#pragma once

#include "LinearInterpolation.h"

template<class T>
class CPhaseSkewer2D
{
public:
    static constexpr T MinX = static_cast<T>(-1);
    static constexpr T MinY = static_cast<T>(-1);
    static constexpr T MaxX = static_cast<T>(1);
    static constexpr T MaxY = static_cast<T>(1);

    CPhaseSkewer2D()
    {}

    T operator()(T Phase, T SkewX, T SkewY)
    {
        return Phase<SkewX ? LinearInterpolation(MinX, MinY, SkewX, SkewY, Phase) : LinearInterpolation(SkewX, SkewY, MaxX, MaxY, Phase);
    }
};
