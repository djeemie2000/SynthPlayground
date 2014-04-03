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
    CController(IView& View, int SamplingFrequency);
    ~CController();

    void OnPlay();
    void OnStop();
    void OnGrab(int GrabSize);
    std::int64_t OnRead(char *Dst, std::int64_t MaxSize);//this should be some different interface?

    void OnFrequency(float Frequency);
    void OnWaveForm(const std::string& WaveForm);

    void OnSmootherFactor(float Factor);

    void OnWaveShaper(const std::string& WaveShaper);
    void OnWaveShaperStrength(float Strength);

private:
    void UpdateFrequency();

    template<class OscillatorType, class ShaperType>
    void FillBuffer(char* Dst, int Size)
    {
        OscillatorType Osc;
        ShaperType Shaper;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Shaper(Osc(m_PhaseGen(m_PhaseStep()))));
            ++pDst;
        }
    }

    IView& m_View;

    bool m_GrabSample;
    CSampleGrabber<std::uint8_t> m_SampleGrabber;

    float m_Frequency;
    CPhaseStep<float> m_PhaseStep;
    CPhaseGenerator<float> m_PhaseGen;
    std::string m_WaveForm;

    std::string m_WaveShaper;
    float m_WaveShaperStrength;

    CSmoother<float> m_Smoother;
};

#endif // GRANULARSAMPLERCONTROLLER_H
