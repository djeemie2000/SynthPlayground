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
#include "DetunedSelectableOscillator.h"

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

    void OnDetune(float Detune);
    void OnDetuneSync();
    void OnDephase(float Dephase);

    void OnSmootherFactor(float Factor);

    void OnBitCrusherDepth(int Depth);
    void OnSampleAndHoldPeriod(int Period);
    void OnRipplerStrength(int Strength);
    void OnRipplerThreshold(int Threshold);

private:
    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    float m_Frequency;
    CDetunedSelectableOscillator<float, 3> m_Oscillator;

    CSmoother<float> m_Smoother;
    C8BitFX m_Fx;
};

#endif // GRANULARSAMPLERCONTROLLER_H
