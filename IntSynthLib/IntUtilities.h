#pragma once

#include <cstdint>

namespace isl
{

template<class T>
T CalcPeriodSamples(std::uint64_t SamplingFrequency, std::uint64_t FrequencyMilliHz)
{
    return SamplingFrequency*1000/FrequencyMilliHz;
}

}//namespace isl
