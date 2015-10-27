#include "UnitTest++.h"
#include "IntScaledValue.h"

namespace
{

using namespace isl;

TEST(Mult1)
{
    CScaledValue<int, 8> Val1(128);
    int Actual = 2*Val1;

    CHECK_EQUAL(1, Actual);
}

TEST(Mult2)
{
    CScaledValue<int, 8> Val1(512);
    int Actual = Val1*2;

    CHECK_EQUAL(4, Actual);
}

TEST(MultScaled)
{
    CScaledValue<int, 8> Val1(512);
    CScaledValue<int, 12> Val2(2048);
    int Actual = Val1*Val2;

    CHECK_EQUAL(1, Actual);
}

}
