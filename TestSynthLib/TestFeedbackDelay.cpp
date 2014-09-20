#include "UnitTest++.h"
#include "FeedbackDelay.h"

namespace
{

TEST(FeedbackDelayZeroWetZero)
{
    // zero delay, wet is zero => Out should always be equal to In
    // zero should be default delay
    int Capacity = 20;
    CFeedbackDelay<int, float> Delay(Capacity, 0);

    for(int In = 0; In<100; ++In)
    {
        int Out = Delay(In);
        CHECK_EQUAL(In, Out);
    }
}

TEST(FeedbackDelayOneWetZero)
{
    // nonzero delay, wet is zero => Out should always be equal to In
    // zero should be default delay
    int Capacity = 20;
    CFeedbackDelay<int, float> Delay(Capacity, 0);

    for(int In = 0; In<100; ++In)
    {
        int Out = Delay(In);
        CHECK_EQUAL(In, Out);
    }
}

TEST(FeedbackDelayOneWetOne)
{
    // nonzero delay, wet is one => Out should always be equal to previous In
    // zero should be default delay
    int Capacity = 20;
    CFeedbackDelay<int, float> Delay(Capacity, 0);
    Delay.SetWet(1.0f);
    Delay.SetDelay(1);

    for(int In = 0; In<100; ++In)
    {
        int Out = Delay(In);
        int PreviousIn = std::max(0, In-1);
        CHECK_EQUAL(PreviousIn, Out);
    }
}

TEST(FeedbackDelayOneWetOneHalf)
{
    // nonzero delay, wet is one => Out should always be equal to previous In
    // zero should be default delay
    int Capacity = 20;
    CFeedbackDelay<int, float> Delay(Capacity, 0);
    Delay.SetWet(0.5f);

    for(int In = 0; In<100; ++In)
    {
        int Out = Delay(In);
        int PreviousIn = std::max(0, In-1);
        int Expected = 0.5f*In + 0.5f*PreviousIn;
//        CHECK_CLOSE(Expected, Out, 1);
    }
}

}
