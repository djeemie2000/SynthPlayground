#include "UnitTest++.h"
#include "IntPhaseGenerator.h"

namespace
{

TEST(Constructor)
{
    CIntegerPhaseGenerator<8> PhaseGen(0);
    CHECK_EQUAL(0, PhaseGen());
}

TEST(PhaseGen8Bits)
{
    const int NumBits = 8;
    CIntegerPhaseGenerator<NumBits> PhaseGen(0);
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
    CIntegerPhaseGenerator<NumBits> PhaseGen(0);
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
    CIntegerPhaseGenerator<NumBits> PhaseGen(0);
    PhaseGen.SetFrequency(40000, 4000);// ideally this generates

    CHECK_EQUAL(25, PhaseGen());
    CHECK_EQUAL(51, PhaseGen());
    CHECK_EQUAL(76, PhaseGen());
    CHECK_EQUAL(102, PhaseGen());
    CHECK_EQUAL(-128, PhaseGen());
    CHECK_EQUAL(-103, PhaseGen());
    CHECK_EQUAL(-77, PhaseGen());
    CHECK_EQUAL(-52, PhaseGen());
    CHECK_EQUAL(-26, PhaseGen());
    CHECK_EQUAL(0, PhaseGen());
}

TEST(PhaseStep12Bits)
{
    const int NumBits = 12;
    CIntegerPhaseGenerator<NumBits> PhaseGen(0);
    PhaseGen.SetFrequency(40000, 2000);// ideally this generates

    CHECK_EQUAL(204, PhaseGen());
    CHECK_EQUAL(409, PhaseGen());
    CHECK_EQUAL(614, PhaseGen());
    CHECK_EQUAL(819, PhaseGen());
    CHECK_EQUAL(1024, PhaseGen());

    CHECK_EQUAL(1228, PhaseGen());
    CHECK_EQUAL(1433, PhaseGen());
    CHECK_EQUAL(1638, PhaseGen());
    CHECK_EQUAL(1843, PhaseGen());
    CHECK_EQUAL(-2048, PhaseGen());

    CHECK_EQUAL(-1844, PhaseGen());
    CHECK_EQUAL(-1639, PhaseGen());
    CHECK_EQUAL(-1434, PhaseGen());
    CHECK_EQUAL(-1229, PhaseGen());
    CHECK_EQUAL(-1024, PhaseGen());

    CHECK_EQUAL(-820, PhaseGen());
    CHECK_EQUAL(-615, PhaseGen());
    CHECK_EQUAL(-410, PhaseGen());
    CHECK_EQUAL(-205, PhaseGen());
    CHECK_EQUAL(0, PhaseGen());
}


}
