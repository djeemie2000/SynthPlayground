#include "UnitTest++.h"
#include "StepSequencer2.h"

namespace
{

TEST(Constructor)
{
    const int SamplingFrequency = 100;
    CStepSequencer2<float, 4> Sequencer(SamplingFrequency);

    //CHECK(!Sequencer.IsRunning());
}

}
