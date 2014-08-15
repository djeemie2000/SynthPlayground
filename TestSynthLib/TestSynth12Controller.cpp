#include "UnitTest++.h"
#include "Synth12Controller.h"

namespace
{

TEST(Read)
{
    CSynth12Controller Controller(44100);

    std::vector<float> Dst(1024, 0.0f);
    Controller.OnRead(Dst.data(), 1024, 100);

    CHECK(true);
}

}
