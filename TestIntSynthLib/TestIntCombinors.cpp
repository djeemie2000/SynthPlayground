#include "UnitTest++.h"
#include "IntCombinors.h"

namespace
{

using namespace isl;

TEST(HardLimitBiPolar)
{
    CHECK_EQUAL(127, (IntHardLimitBipolar<int, 8>(6000)));
    CHECK_EQUAL(20, (IntHardLimitBipolar<int, 8>(20)));
    CHECK_EQUAL(-20, (IntHardLimitBipolar<int, 8>(-20)) );
    CHECK_EQUAL(-128, (IntHardLimitBipolar<int, 8>(-192)) );
}

TEST(HardLimitAdd)
{
    CHECK_EQUAL(127, (IntHardLimitAdd<int, 8>(100, 30)));
    CHECK_EQUAL(20, (IntHardLimitAdd<int, 8>(18, 2)));
    CHECK_EQUAL(-20, (IntHardLimitAdd<int, 8>(20, -40)) );
    CHECK_EQUAL(-128, (IntHardLimitAdd<int, 8>(-192, 50)) );
}

TEST(Mult)
{
    CHECK_EQUAL(32, (IntMult<int, 8>(64, 64)));
    CHECK_EQUAL(0, (IntMult<int, 8>(64, 0)));
    CHECK_EQUAL(-32, (IntMult<int, 8>(64, -64)));
    CHECK_EQUAL(128, (IntMult<int, 8>(64, 256)));
    CHECK_EQUAL(-15, (IntMult<int, 8>(-15, 128)));
}

TEST(MultFirst)
{
    CHECK_EQUAL(32, (IntMultFirst<int, 8>(64, 64)));
    CHECK_EQUAL(0, (IntMultFirst<int, 8>(64, 0)));
    CHECK_EQUAL(32, (IntMultFirst<int, 8>(64, -64)));
    CHECK_EQUAL(128, (IntMultFirst<int, 8>(64, 256)));
    CHECK_EQUAL(-15, (IntMultFirst<int, 8>(-15, 128)));
    CHECK_EQUAL(-15, (IntMultFirst<int, 8>(-15, -128)));
}

TEST(MultSecond)
{
    CHECK_EQUAL(32, (IntMultSecond<int, 8>(64, 64)));
    CHECK_EQUAL(0, (IntMultSecond<int, 8>(64, 0)));
    CHECK_EQUAL(-32, (IntMultSecond<int, 8>(64, -64)));
    CHECK_EQUAL(128, (IntMultSecond<int, 8>(64, 256)));
    CHECK_EQUAL(15, (IntMultSecond<int, 8>(-15, 128)));
    CHECK_EQUAL(15, (IntMultSecond<int, 8>(15, 128)));
    CHECK_EQUAL(-15, (IntMultSecond<int, 8>(-15, -128)));
}

}
