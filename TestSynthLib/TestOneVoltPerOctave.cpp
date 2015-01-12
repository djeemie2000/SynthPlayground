#include "UnitTest++.h"
#include "OneVoltPerOctave.h"

namespace
{

TEST(ToFrequency)
{
    const float Frequency0 = 55.0f;
    COneVoltPerOctave<float> OneVoltPerOctave(Frequency0);

    CHECK_CLOSE(Frequency0, OneVoltPerOctave(0.0f), 0.0001f);
    CHECK_CLOSE(2*Frequency0, OneVoltPerOctave(1.0f), 0.0001f);
    CHECK_CLOSE(4*Frequency0, OneVoltPerOctave(2.0f), 0.0001f);
    CHECK_CLOSE(8*Frequency0, OneVoltPerOctave(3.0f), 0.0001f);

    CHECK_CLOSE(1.4142f*Frequency0, OneVoltPerOctave(0.5f), 0.01f);
    CHECK_CLOSE(2*1.4142f*Frequency0, OneVoltPerOctave(1.5f), 0.01f);

}

}
