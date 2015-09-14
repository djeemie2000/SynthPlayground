#include "UnitTest++.h"
#include "IntOperators.h"

namespace
{

using namespace isl;

TEST(MinMax)
{
    CHECK_EQUAL(128, IntMaxSigned<8>());
    CHECK_EQUAL(-128, IntMinSigned<8>());
}

TEST(SawUp)
{
    CHECK_EQUAL(128, IntSawUp<12>(128));
    CHECK_EQUAL(-128, IntSawUp<8>(-128));
}

TEST(SawDown)
{
    CHECK_EQUAL(-128, IntSawDown<12>(128));
    CHECK_EQUAL(128, IntSawDown<8>(-128));
}

TEST(Pulse)
{
    CHECK_EQUAL(2048, IntPulse<12>(128));
    CHECK_EQUAL(-128, IntPulse<8>(-128));
}

TEST(PseudoSinCalc)
{
    CHECK_EQUAL(0, IntPseudoSinCalc<8>(0));
    CHECK_EQUAL(128, IntPseudoSinCalc<8>(64));
    CHECK_EQUAL(0, IntPseudoSinCalc<8>(128));
}

TEST(FullPseudoSin)
{
    CHECK_EQUAL(0, IntFullPseudoSin<8>(-128));
    CHECK_EQUAL(-56, IntFullPseudoSin<8>(-112));
    CHECK_EQUAL(-128, IntFullPseudoSin<8>(-64));
    CHECK_EQUAL(-96, IntFullPseudoSin<8>(-32));
    CHECK_EQUAL(-56, IntFullPseudoSin<8>(-16));
    CHECK_EQUAL(0, IntFullPseudoSin<8>(0));
    CHECK_EQUAL(56, IntFullPseudoSin<8>(16));
    CHECK_EQUAL(128, IntFullPseudoSin<8>(64));
    CHECK_EQUAL(56, IntFullPseudoSin<8>(112));
    CHECK_EQUAL(0, IntFullPseudoSin<8>(128));
}

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

TEST(SemiPseudoSin)
{
    CHECK_EQUAL(-128, IntSemiPseudoSin<8>(-128));
    CHECK_EQUAL(-68, IntSemiPseudoSin<8>(-112));
    CHECK_EQUAL(64, IntSemiPseudoSin<8>(-64));
    CHECK_EQUAL(112, IntSemiPseudoSin<8>(-32));
    CHECK_EQUAL(124, IntSemiPseudoSin<8>(-16));
    CHECK_EQUAL(128, IntSemiPseudoSin<8>(0));
    CHECK_EQUAL(124, IntSemiPseudoSin<8>(16));
    CHECK_EQUAL(64, IntSemiPseudoSin<8>(64));
    CHECK_EQUAL(-68, IntSemiPseudoSin<8>(112));
    CHECK_EQUAL(-128, IntSemiPseudoSin<8>(128));
}

}
