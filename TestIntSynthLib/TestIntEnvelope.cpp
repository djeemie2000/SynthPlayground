#include "UnitTest++.h"
#include "IntEnvelope.h"

namespace
{

using namespace isl;

TEST(ZeroAttack)
{
    CAEnvelope<int, 10> Envelope;

    Envelope.SetAttack(0);

    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));

    Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
}

TEST(SlowAttack)
{
    CAEnvelope<int, 10> Envelope;

    Envelope.SetAttack((1<<9)+(1<<8));

    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));

    Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope(256));
    CHECK_EQUAL(64, Envelope(256));
    CHECK_EQUAL(128, Envelope(256));
    CHECK_EQUAL(192, Envelope(256));
    CHECK_EQUAL(256, Envelope(256));

}

}
