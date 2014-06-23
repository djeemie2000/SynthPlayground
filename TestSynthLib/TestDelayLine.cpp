#include "UnitTest++.h"
#include "DelayLine.h"

namespace
{

TEST(DelayZero)
{
    // zero delay => Out should always be equal to In
    // zero should be default delay
    int Capacity = 20;
    CDelayLine<int> DelayLine(Capacity, 0);

    for(int In = 0; In<100; ++In)
    {
        int Out = DelayLine(In);
        CHECK_EQUAL(In, Out);
    }
}

TEST(DelayOne)
{
    // one delay => Out should always be equal to previous In
    int Capacity = 20;
    CDelayLine<int> DelayLine(Capacity, 0);
    DelayLine.SetDelay(1);

    for(int In = 0; In<100; ++In)
    {
        int Out = DelayLine(In);
        int PreviousIn = std::max(0, In-1);
        CHECK_EQUAL(PreviousIn, Out);
    }
}

TEST(MaxDelay)
{
    // maximum delay is one below the capacity
    int Capacity = 20;
    CDelayLine<int> DelayLine(Capacity, 0);
    int MaxDelay = Capacity-1;
    DelayLine.SetDelay(MaxDelay);

    for(int In = 0; In<100; ++In)
    {
        int Out = DelayLine(In);
        int Expected = std::max(0, In-MaxDelay);
        CHECK_EQUAL(Expected, Out);
    }
}

}
