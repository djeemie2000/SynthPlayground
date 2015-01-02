#include "UnitTest++.h"
#include "RandomGate.h"

namespace
{

TEST(SomeScalesDefaultCenters)
{
    CRandomGate<float> Gate;

    Gate.SetGateOpenScale(4);
    Gate.SetGateCloseScale(3);

    for(int idx = 0; idx<9; ++idx)
    {
        CHECK_CLOSE(1.0f, Gate(), 0.0001);
    }

    for(int idx = 0; idx<5; ++idx)
    {
        CHECK_CLOSE(0.0f, Gate(), 0.0001);
    }
}

TEST(SomeScalesAndCenters)
{
    CRandomGate<float> Gate;

    Gate.SetGateOpenScale(4);
    Gate.SetGateOpenCenter(0.0f);
    Gate.SetGateCloseScale(3);
    Gate.SetGateCloseCenter(1.0f);

    for(int idx = 0; idx<1; ++idx)
    {
        CHECK_CLOSE(1.0f, Gate(), 0.0001);
    }

    for(int idx = 0; idx<8; ++idx)
    {
        CHECK_CLOSE(0.0f, Gate(), 0.0001);
    }
}



}
