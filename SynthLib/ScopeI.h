#pragma once

#include <vector>
#include <cstdint>

class IScope
{
public:
    typedef const std::vector<std::int16_t> SampleContainerType;

    virtual ~IScope(){}

    virtual void SetSample(const SampleContainerType& Sample) =0;

};
