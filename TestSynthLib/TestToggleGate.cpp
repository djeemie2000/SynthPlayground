#include "UnitTest++.h"
#include "ToggleGate.h"

namespace
{

TEST(SimpleTest)
{
    CToggleGate<float> ToggleGate;

    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        CHECK_CLOSE(0.0f, ToggleGate(0.0f), 0.001f);
    }
    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        CHECK_CLOSE(1.0f, ToggleGate(1.0f), 0.001f);
    }
    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        CHECK_CLOSE(1.0f, ToggleGate(0.0f), 0.001f);
    }
    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        CHECK_CLOSE(0.0f, ToggleGate(1.0f), 0.001f);
    }
    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        CHECK_CLOSE(0.0f, ToggleGate(0.0f), 0.001f);
    }
}

}
