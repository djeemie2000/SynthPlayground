#include "UnitTest++.h"
#include "FMFrequencyModulator.h"

namespace
{

TEST(Constructor)
{
    const int SamplingFrequency = 44100;
    CFMFrequencyModulator<float> FM(SamplingFrequency);

    CHECK_CLOSE(110.0f, FM(110.0f, 0.0f, 2.0f), 0.001f);
}

}
