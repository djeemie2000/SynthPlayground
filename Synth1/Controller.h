#ifndef GRANULARSAMPLERCONTROLLER_H
#define GRANULARSAMPLERCONTROLLER_H

#include <string>
#include <vector>
#include <inttypes.h>
#include "ConstGenerator.h"
#include "GranularSamplePlayer.h"
#include "SampleGrabber.h"
#include "PhaseStep.h"
#include "PhaseGenerator.h"
#include "FeedbackOperator.h"
#include "HardKneeShaper.h"
#include "CenteredShaper.h"

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

    void OnPlay();
    void OnStop();
    void OnGrab(int GrabSize);
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

    void OnOpen(const std::string&);
    void OnSpeed(float Speed);
    void OnLoopingMode(ELoopingMode);
    void OnInterval(int Begin, int End);

    void OnFrequency(float Frequency);
    void OnWaveForm(const std::string& WaveForm);
    void OnFeedback(float Feedback);
    void OnHardKneePhaseShaping(float X, float Y);
    void OnHardKneeWaveShaping(float X, float Y);
    void OnCenteredWaveShaping(float Slope, float Center);

private:
    IView& m_View;

    CConstGenerator<float> m_SampleStep;
    std::vector<std::uint8_t> m_Sample;
    CGranularSamplePlayer<std::uint8_t> m_SamplePlayer;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGen;
    std::string m_WaveForm;
    CFeedbackOperator<float> m_FeedbackOperator;
    CHardKneeShaper<float> m_HardKneePhaseShaper;
    CHardKneeShaper<float> m_HardKneeWaveShaper;
    CCenteredShaper<float> m_CenteredWaveShaper;
};

#endif // GRANULARSAMPLERCONTROLLER_H
