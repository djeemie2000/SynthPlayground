#include "UnitTest++.h"
#include "MultiStepSequencer.h"

namespace
{

TEST(Constructor)
{
    CMultiStepSequencer<float, 8> Sequencer;
    CHECK_EQUAL(0, Sequencer.GetCurrentStep());
    CHECK_EQUAL(0, Sequencer.GetCurrentSubStep());
    CHECK_EQUAL(8, Sequencer.GetMaxNumSteps());
    CHECK_CLOSE(110.0f, Sequencer.GetFrequency(), 0.0001);
    CHECK_CLOSE(1.0f, Sequencer.GetGate(), 0.0001);
}

TEST(StepDefaults)
{
    CMultiStepSequencer<float, 8> Sequencer;

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
    CMultiStepSequencer<float, 8> Sequencer;

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
// TODO different note, octave, velocity per step

}
