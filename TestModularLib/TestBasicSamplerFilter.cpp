#include <vector>
#include <algorithm>
#include "UnitTest++.h"
#include "BasicSamplerFilter.h"

namespace
{


TEST(LoadAWavFileAndPlayIt)
{
    const int SamplingFrequency = 44100;
    CBasicSamplerFilter Filter(SamplingFrequency);

    Filter.OnLoad("/home/pj/Downloads/musicradar-atmospheric-samples-2/Textures/Chitlins.wav");

    const int NumFrames = 4096;
    std::vector<float> GateInBuffer(NumFrames, 1.0f);

    std::vector<float> GateOutBuffer(NumFrames, 0.0f);
    std::vector<float> LeftOutBuffer(NumFrames, 0.0f);
    std::vector<float> RightOutBuffer(NumFrames, 0.0f);

    bool Done = false;
    int Counter = 0;
    while(!Done)
    {
        Filter.OnProcess(
                        {GateInBuffer.data()},
                        {LeftOutBuffer.data(), RightOutBuffer.data(), GateOutBuffer.data()},
                        {},
                        {},
                        NumFrames,
                        0);

        float LeftOutSum =
                        std::accumulate(LeftOutBuffer.begin(), LeftOutBuffer.end(), 0.0f,
                        [](float Sum, float Value){return Sum+std::fabs(Value);});
        if(LeftOutSum<0.001f)
        {
            std::printf("LeftOut sum = %f at %d \r\n", LeftOutSum, Counter);
        }

        float RightOutSum =
                        std::accumulate(RightOutBuffer.begin(), RightOutBuffer.end(), 0.0f,
                        [](float Sum, float Value){return Sum+std::fabs(Value);});
        if(RightOutSum<0.001f)
        {
            std::printf("RightOut sum = %f at %d \r\n", LeftOutSum, Counter);
        }

        if(GateOutBuffer[0]==0.0f)
        {
            Done = true;
            std::printf("GateOut zero at %d \r\n", Counter);
        }

        Counter += NumFrames;
    }

    std::printf("seconds = %f \r\n", static_cast<float>(Counter)/SamplingFrequency);
}

}
