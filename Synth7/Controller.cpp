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
#include "SquareWave.h"
#include "NoOp.h"
#include "Triangle.h"
#include "CrossFader.h"
#include "SelectableCombinor.h"
#include "Combinor.h"
#include "Pitch.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"
#include "Conversions.h"
#include "SelectableCombinorFactory.h"

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
    Op.Add(CQuadratic<float>());
    Op.Add(CInvSquare<float>());
    Op.Add(CSquareWave<float>());
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

    if(Description=="SquareWave")
    {
        return 7;
    }

    return 8;
}



int GetCombinorSelection(const std::string& Description)
{
    if(Description=="+L")
    {
        return 0;
    }
    if(Description=="*")
    {
        return 1;
    }
    if(Description=="M")
    {
        return 2;
    }
    if(Description=="m")
    {
        return 3;
    }
    if(Description=="|-|")
    {
        return 4;
    }
    if(Description=="DivA")
    {
        return 5;
    }
    if(Description=="DivB")
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
    , m_Oscillator(SamplingFrequency, CreateSelectableOperator(), CSelectableCombinorFactory::Create())
    , m_Fold(1.0f)
    , m_Fx()
    , m_LPFilter()
{
    m_Oscillator.SetFrequency(440.0);
    m_Oscillator.Select(0, 0);
    m_Oscillator.Select(1, 0);
    m_Oscillator.SelectCombinor(0);
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
    m_Oscillator.SetFrequency(Frequency);
}

void CController::OnSync()
{
    m_Oscillator.Sync();
}

void CController::OnNoteOn(ENote Note, EOctave Octave)
{
    OnFrequency(CPitch()(Note, Octave));
}

void CController::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{

}

void CController::OnCombinor(int Selected)
{
    m_Oscillator.SelectCombinor(Selected);
}

void CController::OnOperator(int Idx, const std::string &Operator)
{
    m_Oscillator.Select(Idx, GetSelection(Operator));
}

void CController::OnAmplitude(int Idx, float Amplitude)
{
    m_Oscillator.SetAmplitude(Idx, Amplitude);
}

void CController::OnFrequencyMultiplier(int Idx, float FrequencyMultiplier)
{
    m_Oscillator.SetFrequencyMultiplier(Idx, FrequencyMultiplier);
}

void CController::OnPhaseshift(int Idx, float PhaseShift)
{
    m_Oscillator.SetPhaseShift(Idx, PhaseShift);
}

void CController::OnWaveFold(float Fold)
{
    m_Fold = Fold;
}

void CController::OnLPFilterParameter(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
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

void CController::OnGrab(int GrabSize)
{
    m_GrabSample = true;
    m_SampleGrabber.OnGrab(GrabSize);
}

std::int64_t CController::OnRead(char *Dst, std::int64_t MaxSize)
{
    int MaxReadSize = 1<<13;
    std::size_t Size = MaxSize<MaxReadSize ? MaxSize : MaxReadSize;

    CSymmetricalOperator<float> Symm;
    CWaveFold2<float> Fold;
    Fold.SetFold(m_Fold);

    SampleValueType* pDst = reinterpret_cast<SampleValueType*>(Dst);
    SampleValueType* pDstEnd = reinterpret_cast<SampleValueType*>(Dst + Size);
    while(pDst<pDstEnd)
    {
        *pDst = m_Fx(SignedToInt16<float>(m_LPFilter(Symm(m_Oscillator(), Fold))));
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
        m_SampleGrabber.OnRead((SampleValueType*)Dst, Size/2);

        if(m_SampleGrabber.IsSampled())
        {
            // doing this here might cause interuptions in the audio
            m_View.SetSample(m_SampleGrabber.GetSample());

            m_GrabSample = false;//avoid SetSample() over and over again
        }
    }

    return Size;
}
