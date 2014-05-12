#include "UnitTest++.h"
#include "PeriodicConstGenerator.h"

namespace
{

TEST(Constructor)
{
    CPeriodicConstGenerator<float, 4> Generator;
    for(int Idx = 0; Idx<50; ++Idx)
    {
        CHECK_CLOSE(0.0f, Generator(), 0.0001);
    }
}

TEST(SetValue)
{
    CPeriodicConstGenerator<float, 4> Generator;
    Generator.SetValue(0, 0.0f);
    Generator.SetValue(1, 1.0f);
    Generator.SetValue(2, 2.0f);
    Generator.SetValue(3, 3.0f);

    for(int Idx = 1; Idx<50; ++Idx)
    {
        CHECK_CLOSE((Idx%4)*1.0f, Generator(), 0.0001);
    }
}

TEST(SetPeriod)
{
    CPeriodicConstGenerator<float, 4> Generator;
    Generator.SetValue(0, 0.0f);
    Generator.SetValue(1, 1.0f);
    Generator.SetValue(2, 2.0f);
    Generator.SetValue(3, 3.0f);

    int Period = 4;
    Generator.SetPeriod(Period);

    for(int Idx = 1; Idx<50; ++Idx)
    {
        CHECK_CLOSE((Idx/Period%4)*1.0f, Generator(), 0.0001);
    }
}

}
