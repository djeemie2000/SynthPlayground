#include "UnitTest++.h"
#include "Pitch.h"

namespace
{

TEST(SomePitches)
{
    CPitch Pitch;

    CHECK_CLOSE(16.35f, Pitch(ENote::C, EOctave::Octave0), 0.0001f);
}

}
