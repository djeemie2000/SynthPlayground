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

}
