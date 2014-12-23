#include "UnitTest++.h"
#include "ClockPulse.h"

namespace
{

TEST(ClockPulseOut)
{
    const int SamplingFrequency = 1000;
    CClockPulseOut<float> PulseOut(SamplingFrequency);

    PulseOut.SetFrequency(250);

    CHECK_CLOSE(1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(-1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(-1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(-1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(-1.0f, PulseOut(), 0.0001f);
    CHECK_CLOSE(1.0f, PulseOut(), 0.0001f);
}

TEST(ClockPulseInRisingEdge)
{
    CClockPulseIn<float> PulseIn;

    CHECK(!PulseIn.RisingEdge(-1.0f));
    CHECK(!PulseIn.RisingEdge(-1.0f));
    CHECK(PulseIn.RisingEdge(1.0f));
    CHECK(!PulseIn.RisingEdge(1.0f));
    CHECK(!PulseIn.RisingEdge(-1.0f));
    CHECK(!PulseIn.RisingEdge(-1.0f));
}

TEST(ClockPulseInFallingEdge)
{
    CClockPulseIn<float> PulseIn;

    CHECK(!PulseIn.FallingEdge(-1.0f));
    CHECK(!PulseIn.FallingEdge(-1.0f));
    CHECK(!PulseIn.FallingEdge(1.0f));
    CHECK(!PulseIn.FallingEdge(1.0f));
    CHECK(PulseIn.FallingEdge(-1.0f));
    CHECK(!PulseIn.FallingEdge(-1.0f));
}

TEST(ClockPulseInAnyEdge)
{
    CClockPulseIn<float> PulseIn;

    CHECK(!PulseIn.AnyEdge(-1.0f));
    CHECK(!PulseIn.AnyEdge(-1.0f));
    CHECK(PulseIn.AnyEdge(1.0f));
    CHECK(!PulseIn.AnyEdge(1.0f));
    CHECK(!PulseIn.AnyEdge(1.0f));
    CHECK(PulseIn.AnyEdge(-1.0f));
    CHECK(!PulseIn.AnyEdge(-1.0f));
}

}
