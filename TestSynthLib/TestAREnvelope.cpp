#include "UnitTest++.h"
#include "AREnvelope.h"

namespace
{

TEST(Attack10Release20)
{
    CAREnvelope<float> Envelope;

    Envelope.SetAttackSamples(10);
    Envelope.SetReleaseSamples(20);

    for(int idx =0; idx<100; ++idx)
    {
        CHECK_CLOSE(0.0f, Envelope(), 0.01f);
    }

    Envelope.NoteOn();
    for(int idx = 1; idx<10; ++idx)
    {
        CHECK_CLOSE(idx*0.1f, Envelope(), 0.01f);
    }

    for(int idx =0; idx<100; ++idx)
    {
        CHECK_EQUAL(1.0f, Envelope());
    }

    Envelope.NoteOff();
    for(int idx = 1; idx<20; ++idx)
    {
        CHECK_CLOSE(1.0f-idx*0.05f, Envelope(), 0.01f);
    }
}

TEST(Attack0Release0)
{
    CAREnvelope<float> Envelope;

    Envelope.SetAttackSamples(0);
    Envelope.SetReleaseSamples(0);

    for(int idx =0; idx<100; ++idx)
    {
        CHECK_CLOSE(0.0f, Envelope(), 0.01f);
    }

    Envelope.NoteOn();


    for(int idx =0; idx<100; ++idx)
    {
        CHECK_EQUAL(1.0f, Envelope());
    }

    Envelope.NoteOff();
    for(int idx = 1; idx<20; ++idx)
    {
        CHECK_CLOSE(0.0f, Envelope(), 0.01f);
    }
}

}
