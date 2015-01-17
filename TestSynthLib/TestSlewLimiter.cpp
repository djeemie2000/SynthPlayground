#include "UnitTest++.h"
#include "SlewLimiter.h"

namespace
{

TEST(SlewPos)
{
    CSlewLimiter<float> Slew(0.0f);

    CHECK_CLOSE(0.0f, Slew(0.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.25f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.50f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.75f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.00f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.5f, 0.2f), 0.0001f);
}

TEST(SlewNeg)
{
    CSlewLimiter<float> Slew(0.0f);

    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-0.25f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-0.50f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-0.75f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.5f), 0.0001f);
}

}
