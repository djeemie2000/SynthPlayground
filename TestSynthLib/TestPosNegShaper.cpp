#include "UnitTest++.h"
#include "PosNegShaper.h"

namespace
{

const float Epsilon = 0.0001f;

TEST(DefaultInverter)
{
    CPosNegInverter<float> Shaper;

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(DefaultDerectifier)
{
    CPosNegDerectifier<float> Shaper;

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(PosInverter)
{
    CPosNegInverter<float> Shaper;

    Shaper.SetPosInvert(true);

    CHECK_CLOSE(0, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.99, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(NegInverter)
{
    CPosNegInverter<float> Shaper;

    Shaper.SetNegInvert(true);

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.99, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(0.0, Shaper(-1.0), Epsilon);
}

TEST(PosDerectifier)
{
    CPosNegDerectifier<float> Shaper;

    Shaper.SetPosDerectify(true);

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.5), Epsilon);
    CHECK_CLOSE(-0.98, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(NegDerectifier)
{
    CPosNegDerectifier<float> Shaper;

    Shaper.SetNegDerectify(true);

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(1.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(0.98, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

}
