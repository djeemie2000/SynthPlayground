#include "UnitTest++.h"
#include "CombinedOperator.h"

namespace
{

TEST(Constructor)
{
    const int SamplingFrequency = 1000;
    CCombinedOperator<float> Operator(SamplingFrequency);

}

}
