#include "UnitTest++.h"
#include "IntConversions.h"

namespace
{

using namespace isl;

TEST(BipolarToUnipolar)
{
    // [-1,1] to [0,1] or [-2^N, 2^N] to [0, 2^N]
    CHECK_EQUAL(0, IntBipolarToUnipolar<8>(-128));
    CHECK_EQUAL(32, IntBipolarToUnipolar<8>(-64));
    CHECK_EQUAL(64, IntBipolarToUnipolar<8>(0));
    CHECK_EQUAL(96, IntBipolarToUnipolar<8>(64));
    CHECK_EQUAL(128, IntBipolarToUnipolar<8>(128));
}

TEST(UnipolarToBipolar)
{
    // [0,1] to [-1,1]  or [0, 2^N] to [-2^N, 2^N]
    CHECK_EQUAL(-128, IntUnipolarToBipolar<8>(0));
    CHECK_EQUAL(-64, IntUnipolarToBipolar<8>(32));
    CHECK_EQUAL(0, IntUnipolarToBipolar<8>(64));
    CHECK_EQUAL(64, IntUnipolarToBipolar<8>(96));
    CHECK_EQUAL(128, IntUnipolarToBipolar<8>(128));
}

TEST(BipolarToUnsigned)
{
    // [-1,1] to [0,1] or [-2^N, 2^N] to [0, 2^N+1]
    CHECK_EQUAL(0, IntBipolarToUnsigned<8>(-128));
    CHECK_EQUAL(64, IntBipolarToUnsigned<8>(-64));
    CHECK_EQUAL(128, IntBipolarToUnsigned<8>(0));
    CHECK_EQUAL(192, IntBipolarToUnsigned<8>(64));
    CHECK_EQUAL(256, IntBipolarToUnsigned<8>(128));
}

TEST(IntBipolarToFloatBipolar)
{
    // [-2^N, 2^N] to [-1,1]
    CHECK_CLOSE(-0.25f, ( IntBipolarToFloatBipolar<int, float, 10>(-128) ), 0.001f);
    CHECK_CLOSE(-0.125, ( IntBipolarToFloatBipolar<int, float, 10>(-64) ), 0.001f);
    CHECK_CLOSE(0.0f, ( IntBipolarToFloatBipolar<int, float, 10>(0) ), 0.001f);
    CHECK_CLOSE(0.125f, ( IntBipolarToFloatBipolar<int, float, 10>(64) ), 0.001f);
    CHECK_CLOSE(0.25f, ( IntBipolarToFloatBipolar<int, float, 10>(128) ), 0.001f);
    CHECK_CLOSE(0.50f, ( IntBipolarToFloatBipolar<int, float, 10>(256) ), 0.001f);
    CHECK_CLOSE(1.00f, ( IntBipolarToFloatBipolar<int, float, 10>(512) ), 0.001f);
}

TEST(FloatBipolarToIntBipolar)
{
    // [-2^N, 2^N] to [-1,1]
    CHECK_EQUAL(-128, ( FloatBipolarToIntBipolar<int, float, 10>(-0.25f) ));
    CHECK_EQUAL(-64, ( FloatBipolarToIntBipolar<int, float, 10>(-0.125f) ));
    CHECK_EQUAL(0, ( FloatBipolarToIntBipolar<int, float, 10>(0.0f) ));
    CHECK_EQUAL(64, ( FloatBipolarToIntBipolar<int, float, 10>(0.125f) ));
    CHECK_EQUAL(128, ( FloatBipolarToIntBipolar<int, float, 10>(0.25f) ));
    CHECK_EQUAL(256, ( FloatBipolarToIntBipolar<int, float, 10>(0.50f) ));
    CHECK_EQUAL(512, ( FloatBipolarToIntBipolar<int, float, 10>(1.00f) ));
}


}
