#include "UnitTest++.h"
#include "OnePoleFilter.h"

namespace
{

TEST(LowPassIncrease)
{
    COnePoleLowPassFilter<float> Filter;

    const float Parameter = 0.5f;
    CHECK_CLOSE(0.0f, Filter(0.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.0f, Filter(0.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.0f, Filter(0.0f, Parameter), 0.001f);

    CHECK_CLOSE(0.25f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.4375f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.578125f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.683594f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.762695f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.822021f, Filter(1.0f, Parameter), 0.001f);
}

TEST(LowPassIncreaseDecrease)
{
    COnePoleLowPassFilter<float> Filter;

    const float Parameter = 0.9f;

    CHECK_CLOSE(0.81f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.9639f, Filter(1.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.993141f, Filter(1.0f, Parameter), 0.001f);

    CHECK_CLOSE(0.188697f, Filter(0.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.0358524f, Filter(0.0f, Parameter), 0.001f);
    CHECK_CLOSE(0.00681196f, Filter(0.0f, Parameter), 0.001f);
}


}
