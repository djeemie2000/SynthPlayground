#ifndef GRANULARSAMPLERCONTROLLER_H
#define GRANULARSAMPLERCONTROLLER_H

#include <string>
#include <vector>
#include <inttypes.h>
#include "ConstGenerator.h"
#include "GranularSamplePlayer.h"

class IGranularSamplerView;

class CGranularSamplerController
{
public:
    enum class ELoopingMode
    {
        UniDirectional,
        BiDirectional
    };

    CGranularSamplerController(IGranularSamplerView& View, int SamplingFrequency);

    ~CGranularSamplerController();

    void OnOpen(const std::string& Path);

    void OnPlay();

    void OnStop();

    void OnSpeed(float Speed);

    void OnLoopingMode(ELoopingMode Mode);

    void OnInterval(int Begin, int End);

    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);

private:
    IGranularSamplerView& m_View;
    CConstGenerator<float> m_SampleStep;
    std::vector<std::uint8_t> m_Sample;
    CGranularSamplePlayer<std::uint8_t> m_SamplePlayer;
};

#endif // GRANULARSAMPLERCONTROLLER_H
