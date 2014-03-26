#include <cstring>
#include "GranularsamplerController.h"
#include "ReadWavFile.h"
#include "GranularSamplerView.h"

CGranularSamplerController::CGranularSamplerController(IGranularSamplerView &View, int SamplingFrequency)
    : m_View(View)
    , m_SampleStep()
    , m_Sample()
    , m_SamplePlayer()
{
    m_SampleStep.Set(1.0f);
}

CGranularSamplerController::~CGranularSamplerController()
{

}

void CGranularSamplerController::OnOpen(const std::string &Path)
{
    std::vector<std::uint8_t> Values;
    int SamplingFrequency = 0;
    int NumChannels = 0;
    if(readWAVData(Path.c_str(), Values, SamplingFrequency, NumChannels))
    {
        // no support for stereo => should de-interleave if stereo
        if(NumChannels==1)
        {
            // pass values to sample player
            std::swap(m_Sample, Values);
            // adjust view
            m_View.SetSampleSize(m_Sample.size());
            m_View.SetSample(m_Sample);
        }
    }
}

void CGranularSamplerController::OnPlay()
{
    m_SamplePlayer.Reset(m_Sample);
}

void CGranularSamplerController::OnStop()
{

}

void CGranularSamplerController::OnSpeed(float Speed)
{
    m_SampleStep.Set(Speed);
}

void CGranularSamplerController::OnLoopingMode(CGranularSamplerController::ELoopingMode Mode)
{

}

void CGranularSamplerController::OnInterval(int Begin, int End)
{
    m_SamplePlayer.SetInterval(Begin, End);
}

std::int64_t CGranularSamplerController::OnRead(char *Dst, std::int64_t MaxSize)
{
    std::size_t Size = MaxSize<m_Sample.size() ? MaxSize : 8192;//256;

    char* pDst = Dst;
    char* pDstEnd = Dst + Size;
    while(pDst<pDstEnd)
    {
        *pDst = m_SamplePlayer(m_SampleStep());
        ++pDst;
    }

    return Size;

//    //TODO!!!!
//    const int SamplingFrequency = 44100;
//    const int Period = SamplingFrequency / 100;
//    int Sample = 0;
//    char* pDst = Dst;
//    while(Sample<MaxSize)
//    {
//        *pDst = Sample%Period<Period/2 ? 255 : 0;//square?
//        ++pDst;
//        ++Sample;
//    }

//    return MaxSize;
}
