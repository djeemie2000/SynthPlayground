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

CController::CController(IView &View, int SamplingFrequency)
    : m_View(View)
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_Frequency(440.0f)
    , m_PhaseStep(SamplingFrequency)
    , m_PhaseGen()
    , m_WaveForm("NoOp")
    , m_ModifierFrequencyMultiplier(1.0f)
    , m_ModifierPhaseShift(0.0f)
    , m_ModifierPhaseStep(SamplingFrequency)
    , m_ModifierPhaseGen()
    , m_Modifier("NoOp")
    , m_ModifierCondition()
    , m_Smoother()
{
    m_PhaseStep.SetFrequency(440.0);
    m_ModifierPhaseStep.SetFrequency(440.0*m_ModifierFrequencyMultiplier);
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
    m_WaveForm = WaveForm;
}

void CController::OnModifierFrequency(float Frequency)
{
    m_ModifierPhaseStep.SetFrequency(Frequency);
}

void CController::OnSync()
{
    m_PhaseGen.Set(0);
    m_ModifierPhaseGen.Set(0);
}

void CController::OnModifierFrequencyMultiplier(float Multiplier)
{
    m_ModifierFrequencyMultiplier = Multiplier;
    UpdateFrequency();
}

void CController::OnModifierPhaseShift(float PhaseShift)
{
    m_ModifierPhaseShift = PhaseShift;
}

void CController::OnSmootherFactor(float Factor)
{
    m_Smoother.SetFactor(Factor);
}

void CController::UpdateFrequency()
{
    m_PhaseStep.SetFrequency(m_Frequency);
    m_ModifierPhaseStep.SetFrequency(m_Frequency*m_ModifierFrequencyMultiplier);
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

//    CFlipOperator<float> Modifier;
    CMirrorOperator<float> Modifier;
    //CSquare<float> Modifier;
    CPhaseAdder<float> ModifierPhaseShift;
    if(m_WaveForm=="RampUp")
    {
        CRampUp<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="RampDown")
    {
        CRampDown<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="FullPseudoSin")
    {
        CFullPseudoSin<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="PseudoSin")
    {
        CPseudoSin<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="InvSquare")
    {
        CInvSquare<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
//            *pDst = 255*Op(m_PhaseGen(m_PhaseStep()));
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="Square")
    {
        CSquare<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_Smoother(Modifier(m_PhaseGen(m_PhaseStep()), Op, m_ModifierCondition(ModifierPhaseShift(m_ModifierPhaseGen(m_ModifierPhaseStep()), m_ModifierPhaseShift))));
            ++pDst;
        }
    }
    else if(m_WaveForm=="NoOp")
    {
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            float Tmp = m_PhaseGen(m_PhaseStep());
            std::uint8_t Tmp2 = 255*Tmp;
            *pDst = Tmp2;//255*m_PhaseGen(m_PhaseStep());
            ++pDst;
        }
    }

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
