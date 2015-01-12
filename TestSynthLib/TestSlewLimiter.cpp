#include "UnitTest++.h"
#include "SlewLimiter.h"

namespace
{

TEST(SlewPos)
{
    CSlewLimiter<float> Slew(0.0f);

    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.1f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.2f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.3f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.4f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.5f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.6f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.7f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.8f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.9f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(1.0f, Slew(1.0f, 0.1f, 0.2f), 0.0001f);
}

TEST(SlewNeg)
{
    CSlewLimiter<float> Slew(0.0f);

    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(0.0f, Slew(0.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-0.2f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-0.4f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-0.6f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-0.8f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
    CHECK_CLOSE(-1.0f, Slew(-1.0f, 0.1f, 0.2f), 0.0001f);
}

}
