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
#include "PhaseDecreaseCondition.h"

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

    void OnFeedback(float);
    void OnHardKneePhaseShaping(float X, float Y);
    void OnHardKneeWaveShaping(float X, float Y);
    void OnCenteredWaveShaping(float Slope, float Center);

    void OnModifierFrequency(float Frequency);
    void OnModifier(const std::string& Modifier);
    void OnSync(float PhaseShift);
    void OnModifierFrequencyMultiplier(float Multiplier);

private:
    void UpdateFrequency();

    IView& m_View;

    CConstGenerator<float> m_SampleStep;
    std::vector<std::uint8_t> m_Sample;
    CGranularSamplePlayer<std::uint8_t> m_SamplePlayer;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    float m_Frequency;
    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGen;
    std::string m_WaveForm;

    float m_ModifierFrequencyMultiplier;
    CPhaseStep<float> m_ModifierPhaseStep;
    CPhaseGenerator<float> m_ModifierPhaseGen;
    std::string m_Modifier;
    CPhaseDecreaseCondition<float> m_ModifierCondition;
};

#endif // GRANULARSAMPLERCONTROLLER_H
