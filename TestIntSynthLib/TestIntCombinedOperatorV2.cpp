#include "UnitTest++.h"
#include "IntCombinedOperatorV2.h"

namespace
{

using namespace isl;

TEST(Constructor)
{
    CIntCombinedOperatorV2<8, 10, 8> Operator;

    Operator.SetSamplingFrequency(10000);
    Operator.SetFrequency(100*1000);
    Operator.SetFrequencyMultiplierA(1024);
    Operator.SetFrequencyMultiplierB(1024);
    Operator.SelectOperatorA(5);
    Operator.SelectOperatorB(5);
    Operator.SelectCombinor1(0);
    Operator.Sync();
    CHECK_EQUAL(128, Operator());
    CHECK_EQUAL(128, Operator());
    CHECK_EQUAL(128, Operator());
    CHECK_EQUAL(128, Operator());
    CHECK_EQUAL(128, Operator());
}



}
