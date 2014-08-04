#include "UnitTest++.h"
#include "CPosNegShaper.h"

namespace
{

const float Epsilon = 0.0001f;

TEST(Defaults)
{
    CPosNegShaper<float> Shaper;

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(PosInvert)
{
    CPosNegShaper<float> Shaper;

    Shaper.SetPosInvert(true);

    CHECK_CLOSE(0, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.99, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(NegInvert)
{
    CPosNegShaper<float> Shaper;

    Shaper.SetNegInvert(true);

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.5, Shaper(0.5), Epsilon);
    CHECK_CLOSE(0.01, Shaper(0.01), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.99, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(0.0, Shaper(-1.0), Epsilon);
}

TEST(PosDerectify)
{
    CPosNegShaper<float> Shaper;

    Shaper.SetPosDerectify(true);

    CHECK_CLOSE(1, Shaper(1), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.5), Epsilon);
    CHECK_CLOSE(-0.98, Shaper(0.01), Epsilon);
    CHECK_CLOSE(0.0, Shaper(0.0), Epsilon);
    CHECK_CLOSE(-0.01, Shaper(-0.01), Epsilon);
    CHECK_CLOSE(-0.5, Shaper(-0.5), Epsilon);
    CHECK_CLOSE(-1.0, Shaper(-1.0), Epsilon);
}

TEST(NegDerectify)
{
    CPosNegShaper<float> Shaper;

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
