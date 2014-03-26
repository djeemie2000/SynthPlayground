#include <cstring>
#include "Controller.h"
#include "ReadWavFile.h"
#include "View.h"

CController::CController(IView &View, int SamplingFrequency)
    : m_View(View)
    , m_SampleStep()
    , m_Sample()
    , m_SamplePlayer()
    , m_GrabSample(false)
    , m_SampleGrabber()
{
    m_SampleStep.Set(1.0f);
}

CController::~CController()
{

}

void CController::OnOpen(const std::string &Path)
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

void CController::OnLoopingMode(CController::ELoopingMode Mode)
{

}

void CController::OnInterval(int Begin, int End)
{
    m_SamplePlayer.SetInterval(Begin, End);
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

    char* pDst = Dst;
    char* pDstEnd = Dst + Size;
    while(pDst<pDstEnd)
    {
        *pDst = m_SamplePlayer(m_SampleStep());
        ++pDst;
    }

    if(m_GrabSample)
    {
        m_SampleGrabber.OnRead((std::uint8_t*)Dst, MaxSize);

        if(m_SampleGrabber.IsSampled())
        {
            // doing this here might cause interuptions in the audio
            m_View.SetSample(m_SampleGrabber.GetSample());

            m_GrabSample = false;//avoid SetSample() over and over again
        }
    }

    return Size;
}
