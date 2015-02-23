#include "UnitTest++.h"
#include "PhaseShifter.h"

namespace
{

TEST(Test1)
{
    CPhaseShifter<float> Shifter;

    CHECK_CLOSE(0.7f, Shifter(0.5f, 0.2f), 0.001f);
    CHECK_CLOSE(-0.7f, Shifter(-0.9f, 0.2f), 0.001f);
    CHECK_CLOSE(-0.9f, Shifter(0.9f, 0.2f), 0.001f);

    CHECK_CLOSE(0.7f, Shifter(0.9f, -0.2f), 0.001f);
    CHECK_CLOSE(0.9f, Shifter(-0.9f, -0.2f), 0.001f);
    CHECK_CLOSE(-0.7f, Shifter(-0.5f, -0.2f), 0.001f);
}

}
