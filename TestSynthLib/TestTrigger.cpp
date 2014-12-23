#include "UnitTest++.h"
#include "Trigger.h"

namespace
{

TEST(TriggerIn)
{
    CTriggerIn<float> TriggerIn;

    CHECK(!TriggerIn.IsTriggerOn(0.0f));
    CHECK(!TriggerIn.IsTriggerOn(-1.0f));
    CHECK(TriggerIn.IsTriggerOn(1.0f));

    CHECK(!TriggerIn.IsTriggerOff(0.0f));
    CHECK(!TriggerIn.IsTriggerOff(1.0f));
    CHECK(TriggerIn.IsTriggerOff(-1.0f));
}

TEST(GateToTrigger)
{
    CGateToTrigger<float> GateToTrigger;

    CHECK_CLOSE(0.0f, GateToTrigger(0.0f), 0.0001);
    CHECK_CLOSE(0.0f, GateToTrigger(0.0f), 0.0001);

    CHECK_CLOSE(1.0f, GateToTrigger(1.0f), 0.0001);

    CHECK_CLOSE(0.0f, GateToTrigger(1.0f), 0.0001);
    CHECK_CLOSE(0.0f, GateToTrigger(1.0f), 0.0001);
    CHECK_CLOSE(0.0f, GateToTrigger(1.0f), 0.0001);

    CHECK_CLOSE(-1.0f, GateToTrigger(0.0f), 0.0001);

    CHECK_CLOSE(0.0f, GateToTrigger(0.0f), 0.0001);
    CHECK_CLOSE(0.0f, GateToTrigger(0.0f), 0.0001);
}

}

