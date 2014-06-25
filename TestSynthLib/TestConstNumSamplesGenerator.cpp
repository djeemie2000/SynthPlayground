#include "UnitTest++.h"
#include "ConstNumSamplesGenerator.h"

namespace
{

TEST(Constructor)
{
    CConstNumSamplesGenerator<float> Generator(10000);

    CHECK_CLOSE(0.0f, Generator(), 0.0001);
}

TEST(SetMilliSeconds)
{
    CConstNumSamplesGenerator<float> Generator(10000);

    Generator.SetMilliSeconds(1.0f);
    CHECK_CLOSE(10.0f, Generator(), 0.0001);

    Generator.SetMilliSeconds(2000.0f);
    CHECK_CLOSE(20000.0f, Generator(), 0.0001);

    Generator.SetMilliSeconds(0.1f);
    CHECK_CLOSE(1.0f, Generator(), 0.0001);
}

}
