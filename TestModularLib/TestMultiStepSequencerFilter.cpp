#include "UnitTest++.h"
#include "MultiStepSequencerFilter.h"
#include "Pitch.h"

namespace
{

void DoInstantiation()
{
}

TEST(InputOutputNames)
{
    CPitch Pitch;//why is this needed for compilation???????????

    CMultiStepSequencerFilter::CurrentStepCallbackType Callback;
    CMultiStepSequencerFilter Filter(44100, Callback);

    CHECK_EQUAL(1u, Filter.GetInputNames().size());
    CHECK_EQUAL("Clock", Filter.GetInputNames()[0]);
    CHECK_EQUAL(4u, Filter.GetOutputNames().size());
    CHECK_EQUAL("Vel", Filter.GetOutputNames()[0]);
    CHECK_EQUAL("Freq", Filter.GetOutputNames()[1]);
    CHECK_EQUAL("Gate", Filter.GetOutputNames()[2]);
    CHECK_EQUAL("Trigger", Filter.GetOutputNames()[3]);
    CHECK_EQUAL(0u, Filter.GetMidiInputNames().size());
    CHECK_EQUAL(0u, Filter.GetMidiOutputNames().size());
}

TEST(MaxNumSteps)
{
//    CPitch Pitch;//why is this needed for compilation???????????

    CMultiStepSequencerFilter::CurrentStepCallbackType Callback;
    CMultiStepSequencerFilter Filter(44100, Callback);

    CHECK_EQUAL(8, Filter.GetMaxNumSteps());
}

}
