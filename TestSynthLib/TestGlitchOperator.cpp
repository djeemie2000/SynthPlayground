#include <vector>
#include "UnitTest++.h"
#include "GlitchOperator.h"

namespace
{

TEST(Test1)
{
    CGlitchOperator<int> Operator;
    const int NumFrames = 1<<6;
    std::vector<int> Source(NumFrames, 0);
    for(int idx = 0; idx<NumFrames; ++idx)
    {
        Source[idx] = idx;
    }
    std::vector<int> Destination(NumFrames, 0);
    std::vector<int> Expected(NumFrames, 0);

    Operator.SetGrainSize(5);// 2^5 = 32
    Operator.SetGrainOffset(1<<4);//4);// 2^4 = 16
    Operator.SetGrainSpeed(-1);
    Operator.Process(Source.data(), Destination.data(), NumFrames);

    for(int idx = 0; idx<NumFrames; ++idx)
    {
        CHECK_EQUAL(Expected[idx], Destination[idx]);
    }
}

}
