#include "UnitTest++.h"
#include "IntCombinedOperator.h"

namespace
{

using namespace isl;

TEST(Constructor)
{
    CIntCombinedOperator<8> Operator;

    Operator.SetFrequency(10000, 100*1000);
    Operator.SetFrequencyMultiplier(128, 8);
    Operator.Sync();
    CHECK_EQUAL(127, Operator());
    CHECK_EQUAL(127, Operator());
    CHECK_EQUAL(127, Operator());
    CHECK_EQUAL(127, Operator());
    CHECK_EQUAL(127, Operator());
}



}
