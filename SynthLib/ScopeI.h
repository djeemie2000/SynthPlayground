#pragma once

#include <vector>
#include <cstdint>

template<class T>
class IScope
{
public:
    typedef const std::vector<T> SampleContainerType;

    virtual ~IScope(){}

    virtual void SetSample(const SampleContainerType& Sample) =0;
};

class IInt16Scope
{
public:
    typedef const std::vector<std::int16_t> SampleContainerType;

    virtual ~IInt16Scope(){}

    virtual void SetSample(const SampleContainerType& Sample) =0;
};
