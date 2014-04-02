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
#include "Smoother.h"

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

    void OnFrequency(float Frequency);
    void OnWaveForm(const std::string& WaveForm);

    void OnModifierFrequency(float Frequency);
    void OnModifier(const std::string& Modifier);
    void OnSync();
    void OnModifierFrequencyMultiplier(float Multiplier);
    void OnModifierPhaseShift(float PhaseShift);
    void OnSmootherFactor(float Factor);

private:
    void UpdateFrequency();

    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    float m_Frequency;
    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGen;
    std::string m_WaveForm;

    float m_ModifierFrequencyMultiplier;
    float m_ModifierPhaseShift;
    CPhaseStep<float> m_ModifierPhaseStep;
    CPhaseGenerator<float> m_ModifierPhaseGen;
    std::string m_Modifier;
    CPhaseDecreaseCondition<float> m_ModifierCondition;

    CSmoother<float> m_Smoother;
};

#endif // GRANULARSAMPLERCONTROLLER_H
