#include "UnitTest++.h"
#include "Detuner.h"

namespace
{

TEST(NoDetuning)
{
    CDetuner<float> Detuner;

    CHECK_CLOSE(100.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(1234.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(10.0f, Detuner(10.0f), 0.00001f);
}

TEST(OctaveDetuning)
{
    CDetuner<float> Detuner;

    Detuner.SetOctaveShift(2);

    CHECK_CLOSE(400.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(4936.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(40.0f, Detuner(10.0f), 0.00001f);

    Detuner.SetOctaveShift(-2);

    CHECK_CLOSE(25.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(308.5f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(2.5f, Detuner(10.0f), 0.00001f);
}

TEST(SimpleDetuning)
{
    CDetuner<float> Detuner;

    Detuner.SetDetune(1);

    CHECK_CLOSE(200.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(2468.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(20.0f, Detuner(10.0f), 0.00001f);

    Detuner.SetDetune(-1);

    CHECK_CLOSE(50.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(617.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(5.0f, Detuner(10.0f), 0.00001f);
}

TEST(OctaveSimpleDetuning)
{
    CDetuner<float> Detuner;

    Detuner.SetOctaveShift(1);
    Detuner.SetDetune(1);

    CHECK_CLOSE(400.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(4936.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(40.0f, Detuner(10.0f), 0.00001f);

    Detuner.SetDetune(-1);

    CHECK_CLOSE(100.0f, Detuner(100.0f), 0.00001f);
    CHECK_CLOSE(1234.0f, Detuner(1234.0f), 0.00001f);
    CHECK_CLOSE(10.0f, Detuner(10.0f), 0.00001f);
}

}
