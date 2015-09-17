#include "UnitTest++.h"
#include "IntSimpleOscillator.h"

namespace
{

using namespace isl;

TEST(Constructor)
{
    CSimpleOscillator<8> Oscillator(10000);

    Oscillator.SetFrequency(100*1000);

    CHECK_EQUAL(2, Oscillator());
    CHECK_EQUAL(5, Oscillator());
    CHECK_EQUAL(7, Oscillator());
    CHECK_EQUAL(10, Oscillator());
    CHECK_EQUAL(12, Oscillator());

    Oscillator.Sync();

    CHECK_EQUAL(2, Oscillator());
    CHECK_EQUAL(5, Oscillator());
    CHECK_EQUAL(7, Oscillator());
    CHECK_EQUAL(10, Oscillator());
    CHECK_EQUAL(12, Oscillator());
}

}
