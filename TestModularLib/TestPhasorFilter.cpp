#include "UnitTest++.h"
#include "PhasorFilter.h"

namespace
{

TEST(Names)
{
    CPhasorFilter Filter(44100);
    CHECK_EQUAL(1, Filter.GetInputNames().size());
    CHECK_EQUAL("Freq", Filter.GetInputNames()[0]);
    CHECK_EQUAL(1, Filter.GetOutputNames().size());
    CHECK_EQUAL("Phase", Filter.GetOutputNames()[0]);
    CHECK_EQUAL(0, Filter.GetMidiInputNames().size());
}

TEST(Test1)
{
    CPhasorFilter Filter(44100);

    const int BufferSize = 1024;
    std::vector<float> FreqBuffer(BufferSize, 441.0f);
    std::vector<float> PhaseBuffer(BufferSize, 0.0f);
    void* SrcBuffer = FreqBuffer.data();
    void* DstBuffer = PhaseBuffer.data();

    Filter.OnProcess({SrcBuffer}, {DstBuffer}, {}, {}, BufferSize, 1234u);

    CHECK_CLOSE(0.020f, PhaseBuffer[0], 0.001);
    CHECK_CLOSE(0.040f, PhaseBuffer[1], 0.001);
    CHECK_CLOSE(0.060f, PhaseBuffer[2], 0.001);

    CHECK_CLOSE(0.960f, PhaseBuffer[47], 0.001);
    CHECK_CLOSE(0.980f, PhaseBuffer[48], 0.001);
    CHECK_CLOSE(1.000f, PhaseBuffer[49], 0.001);
    CHECK_CLOSE(-0.980f, PhaseBuffer[50], 0.001);

    CHECK_CLOSE(0.020f, PhaseBuffer[100], 0.001);
    CHECK_CLOSE(0.040f, PhaseBuffer[101], 0.001);
    CHECK_CLOSE(0.06f, PhaseBuffer[102], 0.001);

    CHECK_CLOSE(-0.980f, PhaseBuffer[750], 0.001);
    CHECK_CLOSE(0.000f, PhaseBuffer[799], 0.001);
    CHECK_CLOSE(0.020f, PhaseBuffer[800], 0.001);
    CHECK_CLOSE(0.040f, PhaseBuffer[801], 0.001);
    CHECK_CLOSE(0.060f, PhaseBuffer[802], 0.001);


    CHECK_CLOSE(0.20f, PhaseBuffer[1009], 0.001);
    CHECK_CLOSE(0.22f, PhaseBuffer[1010], 0.001);
    CHECK_CLOSE(0.24f, PhaseBuffer[1011], 0.001);
    CHECK_CLOSE(0.26f, PhaseBuffer[1012], 0.001);
}

}
