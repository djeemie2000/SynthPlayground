#include "karplusstrong.h"
#include "UnitTest++.h"

namespace
{

TEST(SomeTest)
{
    const int SamplingFrequency = 100;
    float MinFrequency = 10;
    CKarplusStrong<float> Operator(SamplingFrequency, MinFrequency);

    CHECK_CLOSE(0.0f, Operator(0.0f, 10.0f, 0.90f), 0.001f);
}

}

