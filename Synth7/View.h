

#include <string>
#include <vector>
#include <cstdint>
#include "ConstGenerator.h"
#include "GranularSamplePlayer.h"

class IView
{
public:
    typedef const std::vector<std::int16_t> SampleContainerType;

    virtual ~IView(){}

    virtual void SetSampleSize(int Size) =0;

    virtual void SetSample(const SampleContainerType& Sample) =0;

};
