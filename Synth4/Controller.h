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
#include "SelectableOperator.h"
#include "8BitFX.h"
#include "TriangularLFO.h"

class IView;

class CController
{
public:
    CController(IView& View, int SamplingFrequency);
    ~CController();

    void OnPlay();
    void OnStop();
    void OnGrab(int GrabSize);
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

    void OnFrequency(float Frequency);
    void OnWaveForm(const std::string& WaveForm);

    void OnWaveForm2(const std::string& WaveForm);
    void OnMorpherFrequencyMultiplier(float Multiplier);

    void OnSmootherFactor(float Factor);

    void OnBitCrusherDepth(int Depth);
    void OnSampleAndHoldPeriod(int Period);
    void OnRipplerStrength(int Strength);
    void OnRipplerThreshold(int Threshold);

private:
    void UpdateFrequency();

    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    float m_Frequency;
    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGen;
    CSelectableOperator<float> m_Oscillator;
    CSelectableOperator<float> m_Oscillator2;

    CTriangularLFO<float> m_MorphLFO;

    CSmoother<float> m_Smoother;
    C8BitFX m_Fx;
};

#endif // GRANULARSAMPLERCONTROLLER_H
