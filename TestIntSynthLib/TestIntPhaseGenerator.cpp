#include "UnitTest++.h"
#include "IntPhaseGenerator.h"

namespace
{

TEST(Constructor)
{
    CIntegerPhaseGenerator<int, 8> PhaseGen(0);
    CHECK_EQUAL(0, PhaseGen());
}

TEST(PhaseGen8Bits)
{
    const int NumBits = 8;
    CIntegerPhaseGenerator<int, NumBits> PhaseGen(0);
    PhaseGen.SetPhaseStep(32<<(32-NumBits));
    CHECK_EQUAL(32, PhaseGen());
    CHECK_EQUAL(64, PhaseGen());
    CHECK_EQUAL(96, PhaseGen());
    CHECK_EQUAL(-128, PhaseGen());
    CHECK_EQUAL(-96, PhaseGen());
    CHECK_EQUAL(-64, PhaseGen());
    CHECK_EQUAL(-32, PhaseGen());
    CHECK_EQUAL(0, PhaseGen());
    CHECK_EQUAL(32, PhaseGen());
    CHECK_EQUAL(64, PhaseGen());
    CHECK_EQUAL(96, PhaseGen());
}

TEST(PhaseGen12Bits)
{
    const int NumBits = 12;
    CIntegerPhaseGenerator<int, NumBits> PhaseGen(0);
    PhaseGen.SetPhaseStep(128<<(32-NumBits));
    CHECK_EQUAL(128, PhaseGen());
    CHECK_EQUAL(256, PhaseGen());
    CHECK_EQUAL(384, PhaseGen());
    CHECK_EQUAL(512, PhaseGen());
    CHECK_EQUAL(512+128, PhaseGen());
    CHECK_EQUAL(512+256, PhaseGen());
    CHECK_EQUAL(512+384, PhaseGen());
    CHECK_EQUAL(512+512, PhaseGen());
    //...
}

TEST(PhaseStep8Bits)
{
    const int NumBits = 8;
    CIntegerPhaseGenerator<int, NumBits> PhaseGen(0);
    PhaseGen.SetFrequency(40000, 4000*1000);// ideally this generates
    CHECK_EQUAL( (uint64_t(1)<<32)/10, PhaseGen.GetPhaseStep());

    CHECK_EQUAL(25, PhaseGen());
    CHECK_EQUAL(51, PhaseGen());
    CHECK_EQUAL(76, PhaseGen());
    CHECK_EQUAL(102, PhaseGen());
    CHECK_EQUAL(127, PhaseGen());
    CHECK_EQUAL(-103, PhaseGen());
    CHECK_EQUAL(-77, PhaseGen());
    CHECK_EQUAL(-52, PhaseGen());
    CHECK_EQUAL(-26, PhaseGen());
    CHECK_EQUAL(-1, PhaseGen());
}

TEST(PhaseStep12Bits)
{
    const int NumBits = 12;
    CIntegerPhaseGenerator<int, NumBits> PhaseGen(0);
    PhaseGen.SetFrequency(40000, 2000*1000);// ideally this generates
    CHECK_EQUAL( (uint64_t(1)<<32)/20, PhaseGen.GetPhaseStep());

    CHECK_EQUAL(204, PhaseGen());
    CHECK_EQUAL(409, PhaseGen());
    CHECK_EQUAL(614, PhaseGen());
    CHECK_EQUAL(819, PhaseGen());
    CHECK_EQUAL(1023, PhaseGen());

    CHECK_EQUAL(1228, PhaseGen());
    CHECK_EQUAL(1433, PhaseGen());
    CHECK_EQUAL(1638, PhaseGen());
    CHECK_EQUAL(1843, PhaseGen());
    CHECK_EQUAL(2047, PhaseGen());

    CHECK_EQUAL(-1844, PhaseGen());
    CHECK_EQUAL(-1639, PhaseGen());
    CHECK_EQUAL(-1434, PhaseGen());
    CHECK_EQUAL(-1229, PhaseGen());
    CHECK_EQUAL(-1025, PhaseGen());

    CHECK_EQUAL(-820, PhaseGen());
    CHECK_EQUAL(-615, PhaseGen());
    CHECK_EQUAL(-410, PhaseGen());
    CHECK_EQUAL(-205, PhaseGen());
    CHECK_EQUAL(-1, PhaseGen());
}

TEST(PhaseShift8Bits)
{
    const int NumBits = 8;
    CIntegerPhaseGenerator<int, NumBits> PhaseGen(0);
    PhaseGen.SetPhaseStep(32<<(32-NumBits));

    CHECK_EQUAL(32, PhaseGen());
    CHECK_EQUAL(60, PhaseGen.Shifted(28));
    CHECK_EQUAL(124, PhaseGen.Shifted(92));
    CHECK_EQUAL(126, PhaseGen.Shifted(94));
    CHECK_EQUAL(127, PhaseGen.Shifted(95));
    CHECK_EQUAL(-128, PhaseGen.Shifted(96));
    CHECK_EQUAL(-124, PhaseGen.Shifted(100));
    CHECK_EQUAL(-96, PhaseGen.Shifted(128));
    CHECK_EQUAL(32, PhaseGen.Shifted(256));
}

}
