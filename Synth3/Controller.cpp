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

CController::CController(IView &View, int SamplingFrequency)
    : m_View(View)
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_Frequency(440.0f)
    , m_PhaseStep(SamplingFrequency)
    , m_PhaseGen()
    , m_WaveForm("NoOp")
    , m_WaveShaper("NoOp")
    , m_Smoother()
{
    m_PhaseStep.SetFrequency(440.0);
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

void CController::OnSmootherFactor(float Factor)
{
    m_Smoother.SetFactor(Factor);
}

void CController::OnWaveShaper(const std::string &WaveShaper)
{
    m_WaveShaper = WaveShaper;
}

void CController::OnWaveShaperStrength(float Strength)
{
    m_WaveShaperStrength = Strength;
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

    if(m_WaveForm=="RampUp")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CRampUp<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CRampUp<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CRampUp<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CRampUp<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CRampUp<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CRampUp<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CRampUp<float>, CNoOp<float> >(Dst, Size);
        }
    }
    else if(m_WaveForm=="RampDown")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CRampDown<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CRampDown<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CRampDown<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CRampDown<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CRampDown<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CRampDown<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CRampDown<float>, CNoOp<float> >(Dst, Size);
        }
    }
    else if(m_WaveForm=="FullPseudoSin")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CFullPseudoSin<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CFullPseudoSin<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CFullPseudoSin<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CFullPseudoSin<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CFullPseudoSin<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CFullPseudoSin<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CFullPseudoSin<float>, CNoOp<float> >(Dst, Size);
        }
    }
    else if(m_WaveForm=="PseudoSin")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CPseudoSin<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CPseudoSin<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CPseudoSin<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CPseudoSin<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CPseudoSin<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CPseudoSin<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CPseudoSin<float>, CNoOp<float> >(Dst, Size);
        }
    }
    else if(m_WaveForm=="InvSquare")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CInvSquare<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CInvSquare<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CInvSquare<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CInvSquare<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CInvSquare<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CInvSquare<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CInvSquare<float>, CNoOp<float> >(Dst, Size);
        }
    }
    else if(m_WaveForm=="Square")
    {
        if(m_WaveShaper=="RampUp")
        {
            FillBuffer<CSquare<float>, CRampUp<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="RampDown")
        {
            FillBuffer<CSquare<float>, CRampDown<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="FullPseudoSin")
        {
            FillBuffer<CSquare<float>, CFullPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="PseudoSin")
        {
            FillBuffer<CSquare<float>, CPseudoSin<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="InvSquare")
        {
            FillBuffer<CSquare<float>, CInvSquare<float> >(Dst, Size);
        }
        else if(m_WaveShaper=="Square")
        {
            FillBuffer<CSquare<float>, CSquare<float> >(Dst, Size);
        }
        else
        {
            FillBuffer<CSquare<float>, CNoOp<float> >(Dst, Size);
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
