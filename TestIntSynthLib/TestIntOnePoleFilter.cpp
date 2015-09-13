#include "UnitTest++.h"
#include "IntOnePoleFilter.h"

namespace
{

TEST(LowPassIncrease)
{
    CIntegerOnePoleLowPassFilter<int, 8> Filter(2048);

    const int Parameter = 128;//0.5f;
    Filter.SetParameter(Parameter);
    CHECK_CLOSE(2048, Filter(2048), 0.5f);
    CHECK_CLOSE(2048, Filter(2048), 0.5f);
    CHECK_CLOSE(2048, Filter(2048), 0.5f);

    CHECK_CLOSE(2048+2048*0.25f, Filter(4096), 0.5f);
    CHECK_CLOSE(2048+2048*0.4375f, Filter(4096), 0.5f);
    CHECK_CLOSE(2048+2048*0.578125f, Filter(4096), 0.5f);
    CHECK_CLOSE(2048+2048*0.683594f, Filter(4096), 0.5f);
    CHECK_CLOSE(2048+2048*0.762695f, Filter(4096), 0.5f);
    CHECK_CLOSE(2048+2048*0.822021f, Filter(4096), 0.5f);
}

TEST(LowPassIncrease2)
{
    CIntegerOnePoleLowPassFilter<int, 8> Filter(0);

    const int Parameter = 128;//0.5f;
    Filter.SetParameter(Parameter);
    CHECK_CLOSE(0, Filter(0), 0.5f);
    CHECK_CLOSE(0, Filter(0), 0.5f);
    CHECK_CLOSE(0, Filter(0), 0.5f);

    CHECK_CLOSE(2048*0.25f, Filter(2048), 0.5f);
    CHECK_CLOSE(2048*0.4375f, Filter(2048), 0.5f);
    CHECK_CLOSE(2048*0.578125f, Filter(2048), 0.5f);
    CHECK_CLOSE(2048*0.683594f, Filter(2048), 0.5f);
    CHECK_CLOSE(2048*0.762695f, Filter(2048), 0.5f);
    CHECK_CLOSE(2048*0.822021f, Filter(2048), 0.5f);
}

TEST(LowPassIncreaseDecrease)
{
    CIntegerOnePoleLowPassFilter<int, 8> Filter(2048);

    const int Parameter = 0.9f*256;
    Filter.SetParameter(Parameter);

    CHECK_CLOSE(2048+2048*0.81f, Filter(4096), 300.5f);
    CHECK_CLOSE(2048+2048*0.9639f, Filter(4096), 10.5f);
    CHECK_CLOSE(2048+2048*0.993141f, Filter(4096), 10.5f);

    CHECK_CLOSE(2048+2048*0.188697f, Filter(2048), 10.0f);
    CHECK_CLOSE(2048+2048*0.0358524f, Filter(2048), 10.0f);
    CHECK_CLOSE(2048+2048*0.00681196f, Filter(2048), 10.0f);
}

TEST(LowPassIncreaseDecrease2)
{
    CIntegerOnePoleLowPassFilter<int, 8> Filter(0);

    const int Parameter = 0.9f*256;
    Filter.SetParameter(Parameter);

    CHECK_CLOSE(2048*0.81f, Filter(2048), 300.5f);
    CHECK_CLOSE(2048*0.9639f, Filter(2048), 20.5f);
    CHECK_CLOSE(2048*0.993141f, Filter(2048), 10.5f);

    CHECK_CLOSE(2048*0.188697f, Filter(0), 10.5f);
    CHECK_CLOSE(2048*0.0358524f, Filter(0), 10.5f);
    CHECK_CLOSE(2048*0.00681196f, Filter(0), 10.0f);
}

}
