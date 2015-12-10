#include <vector>
#include "UnitTest++.h"
#include "IntMultiStageEnvelope2.h"

namespace
{

using namespace isl;

TEST(ADEnvelopeNoteOn)
{
    const int NumStages = 2;
    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

    // Attack
    Envelope.SetTarget(0, 0);
    Envelope.SetDuration(0, 4);
    // Decay
    Envelope.SetTarget(1, 256);
    Envelope.SetDuration(1, 8);

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());

    Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(64, Envelope());
    CHECK_EQUAL(128, Envelope());
    CHECK_EQUAL(192, Envelope());
    CHECK_EQUAL(256, Envelope());

    CHECK_EQUAL(224, Envelope());
    CHECK_EQUAL(192, Envelope());
    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(128, Envelope());
    CHECK_EQUAL(96, Envelope());
    CHECK_EQUAL(64, Envelope());
    CHECK_EQUAL(32, Envelope());

    Envelope.NoteOff();

    CHECK_EQUAL(0, Envelope());


    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
}

TEST(ADSEnvelopeNoteOn)
{
    const int NumStages = 3;
    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

    // Attack
    Envelope.SetTarget(0, 0);
    Envelope.SetDuration(0, 2);
    // Decay
    Envelope.SetTarget(1, 256);
    Envelope.SetDuration(1, 3);
    // Sustain / halt
    Envelope.SetTarget(2, 160);
    Envelope.SetDuration(2, 1);
    Envelope.SetAction(2, true, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    Envelope.SetAction(2, false, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());

    Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(128, Envelope());
    CHECK_EQUAL(256, Envelope());

    CHECK_EQUAL(224, Envelope());
    CHECK_EQUAL(192, Envelope());
    CHECK_EQUAL(160, Envelope());

    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
}

TEST(ADSEnvelopeNoteOnNoteOn)
{
    // retrigger upon note on
    const int NumStages = 3;
    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

    // Attack
    Envelope.SetTarget(0, 0);
    Envelope.SetDuration(0, 2);
    // Decay
    Envelope.SetTarget(1, 256);
    Envelope.SetDuration(1, 3);
    // Sustain / halt
    Envelope.SetTarget(2, 160);
    Envelope.SetDuration(2, 1);
    Envelope.SetAction(2, true, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    Envelope.SetAction(2, false, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(0, Envelope());

    Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(128, Envelope());
    CHECK_EQUAL(256, Envelope());

    CHECK_EQUAL(224, Envelope());

    Envelope.Reset();//Envelope.NoteOn();

    CHECK_EQUAL(0, Envelope());
    CHECK_EQUAL(128, Envelope());
    CHECK_EQUAL(256, Envelope());

    CHECK_EQUAL(224, Envelope());
    CHECK_EQUAL(192, Envelope());
    CHECK_EQUAL(160, Envelope());

    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
    CHECK_EQUAL(160, Envelope());
}

TEST(ADSREnvelopeNoteOnNoteOff)
{
    const int NumStages = 3;
    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

    // Attack
    Envelope.SetTarget(0, 0);
    Envelope.SetDuration(0, 2);
    Envelope.SetAction(0, true, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);
    Envelope.SetAction(0, false, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    // Decay
    Envelope.SetTarget(1, 256);
    Envelope.SetDuration(1, 3);
    Envelope.SetAction(1, true, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);
    Envelope.SetAction(1, false, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    // Sustain / Release
    Envelope.SetTarget(2, 160);
    Envelope.SetDuration(2, 5);
    Envelope.SetAction(2, true, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    Envelope.SetAction(2, false, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);

    std::vector<int> Input = { 0, 0, 0,// Attack hold
                               1, 0,//Attack advance
                               0, 0, 0,//Decay advance
                               0, 0, 0, 0, 0, 0, 0,// sustain = Release hold
                               -1, 0, 0, 0, 0,//Release advance
                               0, 0, 0, 0 };// Attack hold
    std::vector<int> Expected = { 0, 0, 0,
                                  0, 128,
                                  256, 224, 192,
                                  160, 160, 160, 160, 160, 160, 160,
                                  160, 128, 96, 64, 32,
                                  0, 0, 0, 0 };
    std::vector<int> ExpectedStage = {0, 0, 0,
                                      0, 0,
                                      1, 1, 1,
                                      2, 2, 2, 2, 2, 2, 2,
                                      2, 2, 2, 2, 2,
                                      0, 0, 0, 0 };
    std::vector<int> ExpectedHold = { 1, 1, 1,
                                      0, 0,
                                      0, 0, 0,
                                      1, 1, 1, 1, 1, 1, 1,
                                      0, 0, 0, 0, 0,
                                      1, 1, 1, 1 };

    std::vector<int> ActualEnvelope;
    std::vector<int> ActualStage;
    std::vector<int> ActualHold;

    for(std::size_t idx = 0; idx<Input.size(); ++idx)
    {
        if(Input[idx]==1)
        {
            Envelope.NoteOn();
        }
        else if(Input[idx]==-1)
        {
            Envelope.NoteOff();
        }

        ActualEnvelope.push_back(Envelope());
        ActualStage.push_back(Envelope.GetStage());
        ActualHold.push_back(Envelope.GetHold()?1:0);
    }

    CHECK_EQUAL(Expected.size(), ActualEnvelope.size());
    CHECK_ARRAY_EQUAL(Expected.data(), ActualEnvelope.data(), Expected.size());
    CHECK_ARRAY_EQUAL(ExpectedStage.data(), ActualStage.data(), Expected.size());
    CHECK_ARRAY_EQUAL(ExpectedHold.data(), ActualHold.data(), Expected.size());
}

TEST(ADSREnvelopeNoteOnDuringHold)
{
    const int NumStages = 3;
    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

    // Attack
    Envelope.SetTarget(0, 0);
    Envelope.SetDuration(0, 2);
    Envelope.SetAction(0, true, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);
    Envelope.SetAction(0, false, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    // Decay
    Envelope.SetTarget(1, 256);
    Envelope.SetDuration(1, 3);
    Envelope.SetAction(1, true, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);
    Envelope.SetAction(1, false, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    // Sustain / Release
    Envelope.SetTarget(2, 160);
    Envelope.SetDuration(2, 5);
    Envelope.SetAction(2, true, CMultiStageEnvelope2<int, NumStages, 8>::HoldAction);
    Envelope.SetAction(2, false, CMultiStageEnvelope2<int, NumStages, 8>::AdvanceAction);

    std::vector<int> Input = { 0, 0, 0,// Attack hold
                               1, 0,//Attack advance
                               0, 0, 0,//Decay advance
                               -1, 0, 0, 0, 0,//Release
                               0, 0, 0, 0 };//halt
    std::vector<int> Expected = { 0, 0, 0,
                                  0, 128,
                                  256, 224, 192,
                                  160, 128, 96, 64, 32,
                                  0, 0, 0, 0 };
    std::vector<int> ExpectedStage =
                                { 0, 0, 0,
                                  0, 1,
                                  1, 1, 2,
                                  2, 2, 2, 2, 0,
                                  0, 0, 0, 0 };

    std::vector<int> ExpectedHold =
                                { 1, 1, 1,
                                  0, 0,
                                  0, 0, 0,
                                  0, 0, 0, 0, 1,
                                  1, 1, 1, 1 };


    std::vector<int> ActualEnvelope;
    std::vector<int> ActualStage;
    std::vector<int> ActualHold;

    for(std::size_t idx = 0; idx<Input.size(); ++idx)
    {
        if(Input[idx]==1)
        {
            Envelope.NoteOn();
        }
        else if(Input[idx]==-1)
        {
            Envelope.NoteOff();
        }

        ActualEnvelope.push_back(Envelope());
        ActualStage.push_back(Envelope.GetStage());
        ActualHold.push_back(Envelope.GetHold()?1:0);
    }

    CHECK_EQUAL(Expected.size(), ActualEnvelope.size());
    CHECK_ARRAY_EQUAL(Expected.data(), ActualEnvelope.data(), Expected.size());
    CHECK_ARRAY_EQUAL(ExpectedStage.data(), ActualStage.data(), Expected.size());
    CHECK_ARRAY_EQUAL(ExpectedHold.data(), ActualHold.data(), Expected.size());
}

//TEST(SRREnvelopeNoteOnNoteOff)
//{
//    const int NumStages = 4;
//    CMultiStageEnvelope2<int, NumStages, 8> Envelope;

//    // Sustain
//    Envelope.SetTarget(0, 128);
//    Envelope.SetDuration(0, 4);
//    Envelope.SetHold(0, true);
//    // Release1
//    Envelope.SetTarget(1, 256);
//    Envelope.SetDuration(1, 3);
//    // Release2
//    Envelope.SetTarget(2, 64);
//    Envelope.SetDuration(2, 4);
//    Envelope.SetHold(2, true);
//    // halt
//    Envelope.SetTarget(3, 0);
//    Envelope.SetDuration(3, 1);

//    std::vector<int> Input = { 0, 0, 0,// halt
//                               1, 0,// hold/Sustain
//                               -1, 0, 0, 0,// sustain
//                               0, 0, 0,// Release1
//                               0, 0, 0, 0,//Release2
//                               0, 0, 0, 0 };//halt
//    std::vector<int> Expected = { 128, 128, 128,
//                                  128, 128,
//                                  128, 160, 192, 224,
//                                  256, 192, 128,
//                                  64, 48, 32, 16,
//                                  0, 0, 0, 0 };
//    std::vector<int> ExpectedStage = {0, 0, 0,
//                                      0, 0,
//                                      0, 0, 0, 0,
//                                      1, 1, 1,
//                                      2, 2, 2, 2,
//                                      3, 3, 3, 3 };
//    std::vector<int> ExpectedHold = { 0, 0, 0,
//                                      1, 1,
//                                      0, 0, 0, 0,
//                                      0, 0, 0,
//                                      0, 0, 0,
//                                      0, 0, 0, 0 };

//    std::vector<int> ActualEnvelope;
//    std::vector<int> ActualStage;
//    std::vector<int> ActualHold;

//    for(std::size_t idx = 0; idx<Input.size(); ++idx)
//    {
//        if(Input[idx]==1)
//        {
//            Envelope.NoteOn();
//        }
//        else if(Input[idx]==-1)
//        {
//            Envelope.NoteOff();
//        }

//        ActualEnvelope.push_back(Envelope());
//        ActualStage.push_back(Envelope.GetStage());
//        ActualHold.push_back(Envelope.GetHold()?1:0);
//    }

//    CHECK_EQUAL(Expected.size(), ActualEnvelope.size());
//    CHECK_ARRAY_EQUAL(Expected.data(), ActualEnvelope.data(), Expected.size());
//    CHECK_ARRAY_EQUAL(ExpectedStage.data(), ActualStage.data(), Expected.size());
//    CHECK_ARRAY_EQUAL(ExpectedHold.data(), ActualHold.data(), Expected.size());
//}

}
