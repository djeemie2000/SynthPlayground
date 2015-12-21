#include "UnitTest++.h"
#include "IntCombinedOperator.h"

namespace
{

using namespace isl;

TEST(Constructor)
{
    CIntCombinedOperator<8> Operator(10000);

    Operator.SetFrequency(100*1000);
    Operator.SetFrequencyMultiplierA(128, 8);
    Operator.SetFrequencyMultiplierB(128, 8);
    Operator.SetFrequencyMultiplierC(128, 8);
    Operator.Sync();
    CHECK_EQUAL(126, Operator());
    CHECK_EQUAL(124, Operator());
    CHECK_EQUAL(122, Operator());
    CHECK_EQUAL(118, Operator());
    CHECK_EQUAL(116, Operator());
}



}
