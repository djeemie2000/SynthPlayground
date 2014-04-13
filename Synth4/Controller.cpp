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
//#include "FlipOperator.h"
//#include "MirrorOperator.h"
#include "NoOp.h"
#include "Triangle.h"
//#include "SymmetricalOperator.h"
#include "CrossFader.h"

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
    , m_Oscillator2(CreateSelectableOperator())
    , m_MorphLFO()
    , m_Smoother()
{
    m_PhaseStep.SetFrequency(440.0);
    m_Oscillator.Select(0);
    m_Oscillator2.Select(0);
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

void CController::OnWaveForm2(const std::string &WaveForm)
{
    m_Oscillator2.Select(GetSelection(WaveForm));
}

void CController::OnMorpherFrequencyMultiplier(float Multiplier)
{
    m_MorphLFO.SetMultiplier(Multiplier);
}

void CController::OnSmootherFactor(float Factor)
{
    m_Smoother.SetFactor(Factor);
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

    CCrossFader<float> Morpher;
    char* pDst = Dst;
    char* pDstEnd = Dst + Size;
    while(pDst<pDstEnd)
    {
        //*pDst = 255*m_MorphLFO(m_PhaseStep());
        *pDst = m_Fx(255*Morpher(m_Oscillator,
                                 m_Oscillator2,
                                 m_PhaseGen(m_PhaseStep()),
                                 m_MorphLFO(m_PhaseStep())));
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
