

#include <string>
#include <vector>
#include <inttypes.h>
#include "ConstGenerator.h"
#include "GranularSamplePlayer.h"

class IGranularSamplerView
{
public:
    typedef const std::vector<std::uint8_t> SampleContainerType;

    virtual ~IGranularSamplerView(){}

    virtual void SetSampleSize(int Size) =0;

    virtual void SetSample(const SampleContainerType& Sample) =0;

};
