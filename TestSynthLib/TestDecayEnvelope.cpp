#include "UnitTest++.h"
#include "DecayEnvelope.h"

namespace
{

TEST(Defaults)
{
    CDecayEnvelope<float> Envelope;

    CHECK_CLOSE(0.999, Envelope(), 0.0001);
    CHECK_CLOSE(0.998001, Envelope(), 0.0001);
    CHECK_CLOSE(0.997003, Envelope(), 0.0001);
    CHECK_CLOSE(0.996006, Envelope(), 0.0001);
    CHECK_CLOSE(0.99501, Envelope(), 0.0001);
    Envelope.NoteOff();
    CHECK_CLOSE(0.994015, Envelope(), 0.0001);
    CHECK_CLOSE(0.993021, Envelope(), 0.0001);

    Envelope.NoteOn();
    CHECK_CLOSE(0.999, Envelope(), 0.0001);
    CHECK_CLOSE(0.998001, Envelope(), 0.0001);
    CHECK_CLOSE(0.997003, Envelope(), 0.0001);
    CHECK_CLOSE(0.996006, Envelope(), 0.0001);
    CHECK_CLOSE(0.99501, Envelope(), 0.0001);
}

}
