#ifndef GRANULARSAMPLERCONTROLLER_H
#define GRANULARSAMPLERCONTROLLER_H

#include <string>
#include <vector>
#include <inttypes.h>
#include "ConstGenerator.h"
#include "GranularSamplePlayer.h"
#include "SampleGrabber.h"

class IView;

class CController
{
public:
    enum class ELoopingMode
    {
        UniDirectional,
        BiDirectional
    };

    CController(IView& View, int SamplingFrequency);

    ~CController();

    void OnOpen(const std::string& Path);

    void OnPlay();

    void OnStop();

    void OnSpeed(float Speed);

    void OnLoopingMode(ELoopingMode Mode);

    void OnInterval(int Begin, int End);

    void OnGrab(int GrabSize);

    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

private:
    IView& m_View;
    CConstGenerator<float> m_SampleStep;
    std::vector<std::uint8_t> m_Sample;
    CGranularSamplePlayer<std::uint8_t> m_SamplePlayer;
    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;
};

#endif // GRANULARSAMPLERCONTROLLER_H
