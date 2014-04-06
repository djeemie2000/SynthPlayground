#include <cstring>
#include "Controller.h"
#include "ReadWavFile.h"
#include "View.h"
#include "RampDown.h"
#include "RampUp.h"
#include "InvSquare.h"
#include "PseudoSin.h"
#include "FullPseudoSin.h"
#include "Square.h"
#include "FlipOperator.h"
#include "MirrorOperator.h"
#include "NoOp.h"
#include "Triangle.h"
#include "SymmetricalOperator.h"

namespace
{

CSelectableOperator<float> CreateSelectableOperator()
{
    CSelectableOperator<float> Op;
    Op.Add(CRampUp<float>());
    Op.Add(CRampDown<float>());
    Op.Add(CTriangle<float>());
    Op.Add(CFullPseudoSin<float>());
    Op.Add(CPseudoSin<float>());
    Op.Add(CSquare<float>());
    Op.Add(CInvSquare<float>());
    Op.Add(CNoOp<float>());

    return Op;
}

int GetSelection(const std::string& Description)
{
    if(Description=="RampUp")
    {
        return 0;
    }

    if(Description=="RampDown")
    {
        return 1;
    }

    if(Description=="Triangle")
    {
        return 2;
    }

    if(Description=="FullPseudoSin")
    {
        return 3;
    }

    if(Description=="PseudoSin")
    {
        return 4;
    }

    if(Description=="Square")
    {
        return 5;
    }

    if(Description=="InvSquare")
    {
        return 6;
    }

    return 7;
}

}

CController::CController(IView &View, int SamplingFrequency)
    : m_View(View)
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_Frequency(440.0f)
    , m_PhaseStep(SamplingFrequency)
    , m_PhaseGen()
    , m_Oscillator(CreateSelectableOperator())
    , m_Shaper(CreateSelectableOperator())
    , m_WaveShaperPhaseShift(0.0f)
    , m_WaveShaperPhaseMultiplier(1.0f)
    , m_WaveShaperStrength(0.0f)
    , m_Smoother()
{
    m_PhaseStep.SetFrequency(440.0);
    m_Oscillator.Select(0);
    m_Shaper.Select(0);
}

CController::~CController()
{

}

void CController::OnPlay()
{
}

void CController::OnStop()
{
}

void CController::OnFrequency(float Frequency)
{
    m_Frequency = Frequency;
    UpdateFrequency();
}

void CController::OnWaveForm(const std::string &WaveForm)
{
    m_Oscillator.Select(GetSelection(WaveForm));
}

void CController::OnSmootherFactor(float Factor)
{
    m_Smoother.SetFactor(Factor);
}

void CController::OnWaveShaper(const std::string &WaveShaper)
{
    m_Shaper.Select(GetSelection(WaveShaper));
}

void CController::OnWaveShaperStrength(float Strength)
{
    m_WaveShaperStrength = Strength;
}

void CController::OnWaveShaperPhaseShift(float PhaseDifference)
{
    m_WaveShaperPhaseShift = PhaseDifference;
}

void CController::OnWaveShaperPhaseMultiplier(float Multiplier)
{
    m_WaveShaperPhaseMultiplier = Multiplier;
}

void CController::OnBitCrusherDepth(int Depth)
{
    m_Fx.SetBitCrusherDepth(Depth);
}

void CController::OnSampleAndHoldPeriod(int Period)
{
    m_Fx.SetSampleAndHoldPeriod(Period);
}

void CController::OnRipplerStrength(int Strength)
{
    m_Fx.SetRipplerStrength(Strength);
}

void CController::OnRipplerThreshold(int Threshold)
{
    m_Fx.SetRipplerThreshold(Threshold);
}

void CController::UpdateFrequency()
{
    m_PhaseStep.SetFrequency(m_Frequency);
}

void CController::OnGrab(int GrabSize)
{
    m_GrabSample = true;
    m_SampleGrabber.OnGrab(GrabSize);
}

std::int64_t CController::OnRead(char *Dst, std::int64_t MaxSize)
{
    int MaxReadSize = 1<<11;
    std::size_t Size = MaxSize<MaxReadSize ? MaxSize : MaxReadSize;

    CPhaseSubtractor<float> Sub;
    CPhaseMultiplier<float> Mult;
    CSymmetricalOperator<float> Symm;
    char* pDst = Dst;
    char* pDstEnd = Dst + Size;
    while(pDst<pDstEnd)
    {
        //*pDst = 255*m_Smoother(m_Shaper(Sub(Mult(m_Oscillator(m_PhaseGen(m_PhaseStep())), m_WaveShaperPhaseMultiplier), m_WaveShaperPhaseShift)));
        *pDst = m_Fx(255*m_Smoother(Symm(Sub(Mult(m_Oscillator(m_PhaseGen(m_PhaseStep())), m_WaveShaperPhaseMultiplier), m_WaveShaperPhaseShift), m_Shaper)));
        ++pDst;
    }

//    else if(m_WaveForm=="NoOp")
//    {
//        char* pDst = Dst;
//        char* pDstEnd = Dst + Size;
//        while(pDst<pDstEnd)
//        {
//            float Tmp = m_PhaseGen(m_PhaseStep());
//            std::uint8_t Tmp2 = 255*Tmp;
//            *pDst = Tmp2;//255*m_PhaseGen(m_PhaseStep());
//            ++pDst;
//        }
//    }

    if(m_GrabSample)
    {
        m_SampleGrabber.OnRead((std::uint8_t*)Dst, Size);

        if(m_SampleGrabber.IsSampled())
        {
            // doing this here might cause interuptions in the audio
            m_View.SetSample(m_SampleGrabber.GetSample());

            m_GrabSample = false;//avoid SetSample() over and over again
        }
    }

    return Size;
}
