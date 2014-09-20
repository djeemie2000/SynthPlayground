#include "UnitTest++.h"
#include "ADSREnvelope.h"

namespace
{

const float Delta = 0.0001;

TEST(DefaultEnvelope)
{
    CADSREnvelope<float> Envelope;

    // pre note on
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);

    // note on => immediate attack, zero decay, sustain is 1
    Envelope.NoteOn();
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);

    // note off => imeediate release
    Envelope.NoteOff();
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
}

TEST(NonDefaultEnvelope)
{
    CADSREnvelope<float> Envelope;

    Envelope.SetAttackSamples(2);
    Envelope.SetDecaySamples(4);
    Envelope.SetSustain(0.25);
    Envelope.SetReleaseSamples(5);

    // pre note on
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);

    // note on => attack
    Envelope.NoteOn();
    CHECK_CLOSE(0.5f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);

    // decay
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(0.75f, Envelope(), Delta);
    CHECK_CLOSE(0.5f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);

    // sustain
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);

    // note off => release
    Envelope.NoteOff();
    CHECK_CLOSE(0.20f, Envelope(), Delta);
    CHECK_CLOSE(0.15f, Envelope(), Delta);
    CHECK_CLOSE(0.10f, Envelope(), Delta);
    CHECK_CLOSE(0.05f, Envelope(), Delta);

    // silence
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
}

TEST(SustainOneEnvelope)
{
    CADSREnvelope<float> Envelope;

    Envelope.SetAttackSamples(4);
    Envelope.SetDecaySamples(4);
    Envelope.SetSustain(1.00);
    Envelope.SetReleaseSamples(4);

    // pre note on
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);

    // note on => attack
    Envelope.NoteOn();
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.5f, Envelope(), Delta);
    CHECK_CLOSE(0.75f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);

    // decay
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);

    // sustain
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);
    CHECK_CLOSE(1.0f, Envelope(), Delta);

    // note off => release
    Envelope.NoteOff();
    CHECK_CLOSE(0.75f, Envelope(), Delta);
    CHECK_CLOSE(0.50f, Envelope(), Delta);
    CHECK_CLOSE(0.25f, Envelope(), Delta);
    CHECK_CLOSE(0.00f, Envelope(), Delta);

    // silence
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
    CHECK_CLOSE(0.0f, Envelope(), Delta);
}

}
