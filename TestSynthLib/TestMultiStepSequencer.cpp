#include "UnitTest++.h"
#include "MultiStepSequencer.h"

namespace
{

TEST(Constructor)
{
    CMultiStepSequencer<float, 8> Sequencer();

    //CHECK(!Sequencer.IsRunning());
}

}
