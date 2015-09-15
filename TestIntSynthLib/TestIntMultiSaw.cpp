#include "UnitTest++.h"
#include "IntMultiSaw.h"

namespace
{

using namespace isl;

TEST(ConstructorAllZeroShift)
{
    const int NumSaws = 8;
    CIntMultiSaw<int, NumSaws, 10> MultiSaw;

    MultiSaw.SetFrequency(10000, 1000*1000);

    CHECK_EQUAL(102, MultiSaw());
    CHECK_EQUAL(204, MultiSaw());
    CHECK_EQUAL(307, MultiSaw());
    CHECK_EQUAL(409, MultiSaw());
    CHECK_EQUAL(511, MultiSaw());
    CHECK_EQUAL(-410, MultiSaw());
    CHECK_EQUAL(-308, MultiSaw());
    CHECK_EQUAL(-205, MultiSaw());
    CHECK_EQUAL(-103, MultiSaw());
    CHECK_EQUAL(-1, MultiSaw());
    CHECK_EQUAL(102, MultiSaw());
    CHECK_EQUAL(204, MultiSaw());
    CHECK_EQUAL(307, MultiSaw());
    CHECK_EQUAL(409, MultiSaw());
}


TEST(AllZeroShift)
{
    const int NumSaws = 8;
    CIntMultiSaw<int, NumSaws, 10> MultiSaw;

    MultiSaw.SetFrequency(10000, 1000*1000);

    int PhaseShift[NumSaws] = { 0, 0, 0, 0, 0, 0, 0, 0};
    CHECK_EQUAL(102, MultiSaw(PhaseShift));
    CHECK_EQUAL(204, MultiSaw(PhaseShift));
    CHECK_EQUAL(307, MultiSaw(PhaseShift));
    CHECK_EQUAL(409, MultiSaw(PhaseShift));
    CHECK_EQUAL(511, MultiSaw(PhaseShift));
    CHECK_EQUAL(-410, MultiSaw(PhaseShift));
    CHECK_EQUAL(-308, MultiSaw(PhaseShift));
    CHECK_EQUAL(-205, MultiSaw(PhaseShift));
    CHECK_EQUAL(-103, MultiSaw(PhaseShift));
    CHECK_EQUAL(-1, MultiSaw(PhaseShift));
    CHECK_EQUAL(102, MultiSaw(PhaseShift));
    CHECK_EQUAL(204, MultiSaw(PhaseShift));
    CHECK_EQUAL(307, MultiSaw(PhaseShift));
    CHECK_EQUAL(409, MultiSaw(PhaseShift));
}

}
