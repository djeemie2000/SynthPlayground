#include <cstdint>
#include <iostream>
#include "Synth12Controller.h"
#include "SymmetricalOperator.h"
#include "Amp.h"
#include "ReadWavFile.h"

CSynth12Controller::CSynth12Controller(int SamplingFrequency)
 : m_CarrierWaveTable()
 , m_CarrierPhaseStep(SamplingFrequency)
 , m_CarrierPhase()
 , m_Envelope()
 , m_Fold()
 , m_LPFilterCutoff()
 , m_LPFilter()
 , m_MasterVolume()
{
}

void CSynth12Controller::OnNoteOn(int /*Note*/, int, std::uint32_t /*TimeStamp*/)
{
    m_CarrierPhase.Sync();
    // envelope/gate to 1
    m_Envelope.NoteOn();
}

void CSynth12Controller::OnNoteOff(int /*Note*/, int, std::uint32_t /*TimeStamp*/)
{
    // envelope/gate to 0
    m_Envelope.NoteOff();
}

void CSynth12Controller::OnController(int, int, std::uint32_t)
{

}

void CSynth12Controller::OnPitchbend(int, std::uint32_t)
{

}

void CSynth12Controller::OnUnknown(std::uint32_t)
{

}

void CSynth12Controller::OpenCarrierWaveTable(const std::string &Path)
{
    // read wav file -> format -> convert to float -> set on wavetable
//    if(false)
//    {
//        std::cout << "Opened header" << Path << std::endl;
//        std::cout << "fs=" << SamplingFrequency << " Ch=" << NumChannels << " Bps=" << BitSize << std::endl;
//        //TODO conversion, stereo to mono (l,r, mix), ...
//        int bs = 0;
//    }
//    else
//    {
//        std::cout << "Failed to open " << Path << std::endl;
//    }
}

void CSynth12Controller::OnCarrierPlaybackSpeed(float Speed)
{
    m_CarrierPhaseStep.SetPlaybackSpeed(Speed);
}

void CSynth12Controller::OnWaveFold(float Fold)
{
    m_Fold.Set(Fold);
}

void CSynth12Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
    m_LPFilterCutoff.Set(Parameter);
}

void CSynth12Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth12Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CSynth12Controller::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}

int CSynth12Controller::OnRead(void *Dst, int NumFrames, std::uint32_t /*TimeStamp*/)
{
    CSymmetricalOperator<float> SymmWaveFold;
    CWaveFold2<float> WaveFolder;

    float* pDst = reinterpret_cast<float*>(Dst);
    float* pDstEnd = pDst + NumFrames;

    while(pDst<pDstEnd)
    {
        *pDst = m_MasterVolume()*( m_LPFilter( SymmWaveFold( m_Envelope() * m_CarrierWaveTable(m_CarrierPhase(m_CarrierPhaseStep())), WaveFolder, m_Fold()) ) );
        ++pDst;
    }

    return 0; // zero means ok
}
