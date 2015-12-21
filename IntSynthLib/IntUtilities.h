#pragma once

#include <cstdint>

namespace isl
{

template<class T>
T CalcPeriodSamples(std::uint64_t SamplingFrequency, std::uint64_t FrequencyMilliHz)
{
    return FrequencyMilliHz ? SamplingFrequency*1000/FrequencyMilliHz : 0;
}

template<class T, int Scale>
T Interpolate(T Value1, T Value2, T Interpolation)
{
    // Interpolation = 0 => Value2
    // Interpolation = 1<<Scale => Value1
    return ( Interpolation*Value1 + ((1<<Scale)-Interpolation)*Value2 )>>Scale;
}

}//namespace isl
