#include "PolyKarplusStrong.h"
#include "UnitTest++.h"

namespace
{

TEST(SomeTest)
{
    const int SamplingFrequency = 100;
    const int MinFrequency = 10;
    synthlib::CPolyKarplusStrong<float, SamplingFrequency/MinFrequency, 8> Operator;
    Operator.SetSamplingFrequency(SamplingFrequency);

    Operator.Excite(0.5f, 110.0f, 0.8f, 50.0f, 0.0f);
    CHECK_CLOSE(0.0f, Operator(), 0.001f);
}

}

