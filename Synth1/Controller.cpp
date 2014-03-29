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

CController::CController(IView &View, int SamplingFrequency)
    : m_View(View)
    , m_SampleStep()
    , m_Sample()
    , m_SamplePlayer()
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_PhaseStep(SamplingFrequency)
    , m_PhaseGen()
    , m_WaveForm("NoOp")
    , m_FeedbackOperator()
    , m_HardKneeShaper()
{
    m_SampleStep.Set(1.0f);
    m_PhaseStep.SetFrequency(440.0);
}

CController::~CController()
{

}

void CController::OnOpen(const std::string &)
{
    // for now, create some dummy sample
    // and pass it to the view

    m_Sample.assign(2048, 128);
    for(int idx = 0; idx<2048; ++idx)
    {
        m_Sample[idx] = (idx*2)%256;//saw up period = 128 => freq = samplingfreq/128 ~ 300 Hz?
    }

    m_View.SetSampleSize(m_Sample.size());
    //m_View.SetSample(m_Sample);

//    std::vector<std::uint8_t> Values;
//    int SamplingFrequency = 0;
//    int NumChannels = 0;
//    if(readWAVData(Path.c_str(), Values, SamplingFrequency, NumChannels))
//    {
//        // no support for stereo => should de-interleave if stereo
//        if(NumChannels==1)
//        {
//            // pass values to sample player
//            std::swap(m_Sample, Values);
//            // adjust view
//            m_View.SetSampleSize(m_Sample.size());
//            m_View.SetSample(m_Sample);
//        }
//    }
}

void CController::OnPlay()
{
    m_SamplePlayer.Reset(m_Sample);
}

void CController::OnStop()
{

}

void CController::OnSpeed(float Speed)
{
    m_SampleStep.Set(Speed);
}

void CController::OnLoopingMode(CController::ELoopingMode )
{

}

void CController::OnInterval(int Begin, int End)
{
    m_SamplePlayer.SetInterval(Begin, End);
}

void CController::OnFrequency(float Frequency)
{
    m_PhaseStep.SetFrequency(Frequency);
}

void CController::OnWaveForm(const std::string &WaveForm)
{
    m_WaveForm = WaveForm;
}

void CController::OnFeedback(float Feedback)
{
    m_FeedbackOperator.SetFeedback(Feedback);
}

void CController::OnHardKneePhaseShaping(float X, float Y)
{
    m_HardKneeShaper.SetKnee(X,Y);
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

//    char* pDst = Dst;
//    char* pDstEnd = Dst + Size;
//    while(pDst<pDstEnd)
//    {
//        *pDst = m_SamplePlayer(m_SampleStep());
//        ++pDst;
//    }

    if(m_WaveForm=="RampUp")
    {
        CRampUp<float> Op;
        char* pDst = Dst;
        char* pDstEnd = Dst + Size;
        while(pDst<pDstEnd)
        {
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
            *pDst = 255*m_FeedbackOperator(m_HardKneeShaper(m_PhaseGen(m_PhaseStep())), Op);
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
