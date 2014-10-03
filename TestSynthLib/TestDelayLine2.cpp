#include "UnitTest++.h"
#include "DelayLine2.h"

namespace
{

TEST(DelayZero)
{
    // zero delay => Out should always be equal to In
    // zero should be default delay
    int Capacity = 10;
    CDelayLine2<int> DelayLine(Capacity, 0);

    for(int In = 0; In<23; ++In)
    {
        DelayLine.Write(In);
        int Out = DelayLine.Read(0);
        CHECK_EQUAL(In, Out);
    }
}

TEST(DelayOne)
{
    // one delay => Out should always be equal to previous In
    int Capacity = 9;
    CDelayLine2<int> DelayLine(Capacity, 0);

    for(int In = 0; In<23; ++In)
    {
        DelayLine.Write(In);
        int Out = DelayLine.Read(1);
        int PreviousIn = std::max(0, In-1);
        CHECK_EQUAL(PreviousIn, Out);
    }
}

TEST(DelayTwo)
{
    // one delay => Out should always be equal to previous In
    int Capacity = 10;
    CDelayLine2<int> DelayLine(Capacity, 0);

    for(int In = 0; In<23; ++In)
    {
        DelayLine.Write(In);
        int Out = DelayLine.Read(2);
        int PreviousIn = std::max(0, In-2);
        CHECK_EQUAL(PreviousIn, Out);
    }
}

TEST(MaxDelay)
{
    // maximum delay is one below the capacity
    int Capacity = 20;
    CDelayLine2<int> DelayLine(Capacity, 0);
    int MaxDelay = Capacity-1;

    for(int In = 0; In<100; ++In)
    {
        DelayLine.Write(In);
        int Out = DelayLine.Read(MaxDelay);
        int Expected = std::max(0, In-MaxDelay);
        CHECK_EQUAL(Expected, Out);
    }
}

TEST(DelayVariable)
{
    // zero delay => Out should always be equal to In
    // zero should be default delay
    int Capacity = 10;
    CDelayLine2<int> DelayLine(Capacity, 0);

    for(int In = 0; In<Capacity; ++In)
    {
        DelayLine.Write(In);
    }

    for(int Delay = 0; Delay<Capacity; ++Delay)
    {
        int Out = DelayLine.Read(Delay);
        int Expected = Capacity-1-Delay;
        CHECK_EQUAL(Expected, Out);
    }

}

}
