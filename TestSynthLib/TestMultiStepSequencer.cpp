#include "UnitTest++.h"
#include "MultiStepSequencer.h"

namespace
{

TEST(Constructor)
{
    CMultiStepSequencer Sequencer(8);
    CHECK_EQUAL(0, Sequencer.GetCurrentStep());
    CHECK_EQUAL(0, Sequencer.GetCurrentSubStep());
    CHECK_EQUAL(8, Sequencer.GetMaxNumSteps());
    CHECK_CLOSE(110.0f, Sequencer.GetFrequency(), 0.0001);
    CHECK_CLOSE(1.0f, Sequencer.GetGate(), 0.0001);
}

TEST(StepDefaults)
{
    CMultiStepSequencer Sequencer(8);

    for(int Step = 0; Step<20; ++Step)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            CHECK_EQUAL(Step%8, Sequencer.GetCurrentStep());
            CHECK_EQUAL(0, Sequencer.GetCurrentSubStep());
            const int DefaultDuration = 64;
            float ExpectedGate = ClockPulse<DefaultDuration ? 1.0f : 0.0f;
            CHECK_CLOSE(ExpectedGate, Sequencer.GetGate(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }
}

TEST(StepSubSteps)
{
    const int DefaultDuration = 64;
    CMultiStepSequencer Sequencer(8);

    Sequencer.SetNumSubSteps(3, 2);
    Sequencer.SetNumSubSteps(7, 4);

    for(int Step = 0; Step<3; ++Step)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            CHECK_EQUAL(Step%8, Sequencer.GetCurrentStep());
            CHECK_EQUAL(0, Sequencer.GetCurrentSubStep());
            CHECK_CLOSE(ClockPulse<DefaultDuration ? 1.0f : 0.0f, Sequencer.GetGate(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }

    for(int SubStep = 0; SubStep<2; ++SubStep)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            CHECK_EQUAL(3, Sequencer.GetCurrentStep());
            CHECK_EQUAL(SubStep, Sequencer.GetCurrentSubStep());
            CHECK_CLOSE(ClockPulse<DefaultDuration ? 1.0f : 0.0f, Sequencer.GetGate(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }

    for(int Step = 4; Step<7; ++Step)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            CHECK_EQUAL(Step, Sequencer.GetCurrentStep());
            CHECK_EQUAL(0, Sequencer.GetCurrentSubStep());
            CHECK_CLOSE(ClockPulse<DefaultDuration ? 1.0f : 0.0f, Sequencer.GetGate(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }

    for(int SubStep = 0; SubStep<4; ++SubStep)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            CHECK_EQUAL(7, Sequencer.GetCurrentStep());
            CHECK_EQUAL(SubStep, Sequencer.GetCurrentSubStep());
            CHECK_CLOSE(ClockPulse<DefaultDuration ? 1.0f : 0.0f, Sequencer.GetGate(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }
}

// TODO gate mode single + one/multiple substeps
// TODO gate mode length + one/multiple substeps

TEST(StepFrequencyVelocity)
{
    CMultiStepSequencer Sequencer(8);

    Sequencer.SetNote(0, ENote::C);
    Sequencer.SetOctave(0, EOctave::Octave0);
    Sequencer.SetVelocity(0, 127);


    Sequencer.SetNote(1, ENote::D);
    Sequencer.SetOctave(1, EOctave::Octave5);
    Sequencer.SetVelocity(1, 16);

    CHECK(false);//the following will fail!!!
    for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
    {
//        float ExpectedFrequency = 16.35f;
//        CHECK_CLOSE(ExpectedFrequency, Sequencer.GetFrequency(), 0.0001);
//        float ExpectedVelocity = 127/128.0f;
//        CHECK_CLOSE(ExpectedVelocity, Sequencer.GetVelocity(), 0.0001);
        Sequencer.AdvanceClock();
    }

    for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
    {
        float ExpectedFrequency = 587.33f;
        CHECK_CLOSE(ExpectedFrequency, Sequencer.GetFrequency(), 0.0001);
        float ExpectedVelocity = 16/128.0f;
        CHECK_CLOSE(ExpectedVelocity, Sequencer.GetVelocity(), 0.0001);
        Sequencer.AdvanceClock();
    }

    for(int Step = 2; Step<8; ++Step)
    {
        for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
        {
            float ExpectedFrequency = 110.0f;
            CHECK_CLOSE(ExpectedFrequency, Sequencer.GetFrequency(), 0.0001);
            float ExpectedVelocity = 92/128.0f;
            CHECK_CLOSE(ExpectedVelocity, Sequencer.GetVelocity(), 0.0001);
            Sequencer.AdvanceClock();
        }
    }

    for(int ClockPulse = 0; ClockPulse<128; ++ClockPulse)
    {
        float ExpectedFrequency = 16.35f;
        CHECK_CLOSE(ExpectedFrequency, Sequencer.GetFrequency(), 0.0001);
        float ExpectedVelocity = 127/128.0f;
        CHECK_CLOSE(ExpectedVelocity, Sequencer.GetVelocity(), 0.0001);
        Sequencer.AdvanceClock();
    }
}

}
