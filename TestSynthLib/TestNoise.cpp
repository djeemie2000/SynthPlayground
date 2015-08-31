#include <vector>
#include "UnitTest++.h"
#include "Noise.h"

namespace
{

TEST(Test1)
{
    CNoise<float> Noise;

    for(int Repeat = 0; Repeat<100; ++Repeat)
    {
        float Actual = Noise();
        CHECK(-1.0f<=Actual);
        CHECK(Actual<=1.0f);
    }
}

TEST(Test1Integer)
{
    CNoise<int> Noise;
    std::vector<std::uint32_t> Expected = { 4009202705, 2593574640, 4225104667, 1807830018, 1807034325, 3960698500, 2844327103, 3763679990, 3389376601, 3990143448 };
    for(int Repeat = 0; Repeat<Expected.size(); ++Repeat)
    {
        std::uint32_t Actual = Noise.Rand();
        CHECK_EQUAL(Expected[Repeat], Actual);
    }
}

}
