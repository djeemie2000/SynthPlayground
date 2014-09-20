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

}
