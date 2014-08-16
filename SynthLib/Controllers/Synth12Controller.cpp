#include <cstdint>
#include <iostream>
#include "Synth12Controller.h"
#include "SymmetricalOperator.h"
#include "Amp.h"
#include "WavFileReader.h"
#include "Notes.h"
#include "MidiNoteConverter.h"
#include "Pitch.h"

CSynth12Controller::CSynth12Controller(int SamplingFrequency)
 : m_CarrierWaveTable()
 , m_CarrierPhaseStep(SamplingFrequency)
 , m_CarrierPhase()
 , m_CarrierPlaybackSpeedMultiplier(1)
 , m_CarrierPhaseInverter()
 , m_Inverter()
 , m_Derectifier()
 , m_Envelope()
 , m_Fold()
 , m_LPFilterCutoff()
 , m_LPFilter()
 , m_Distortion()
 , m_MasterVolume()
{
    m_Fold.Set(1);
    m_LPFilterCutoff.Set(1);
    m_MasterVolume.Set(1);
}

void CSynth12Controller::OnNoteOn(int Note, int, std::uint32_t /*TimeStamp*/)
{
    // playbackspeed is multiplied by note pitch / ref note pitch
    // ref note is A3
    float ReferencePitch = CPitch()(ENote::A, EOctave::Octave3);
    float CurrentPitch = CPitch()(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
    m_CarrierPlaybackSpeedMultiplier = CurrentPitch/ReferencePitch;

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
    CWavFileReader Reader;
    if(Reader.Read(Path))
    {
        std::cout << "Opened file" << Path << std::endl;
        std::cout << "fs=" << Reader.GetSamplingFrequency() << std::endl;

        m_CarrierWaveTable.Set(Reader.GetLeft(), Reader.GetSamplingFrequency());
        m_CarrierPhaseStep.Set(Reader.GetSamplingFrequency(), Reader.GetSize());
    }
    else
    {
        std::cout << "Failed to open " << Path << std::endl;
    }
}

void CSynth12Controller::OnCarrierPlaybackSpeed(float Speed)
{
    m_CarrierPhaseStep.SetPlaybackSpeed(Speed);
}

void CSynth12Controller::OnCarrierReverse(bool Invert)
{
    m_CarrierPhaseInverter.SetPosInvert(Invert);
}

void CSynth12Controller::OnWaveFold(float Fold)
{
    if(0<Fold)
    {
        m_Fold.Set(Fold);
    }
}

void CSynth12Controller::SetInverterMode(int Mode)
{
    // TODO use bitwise ands on Mode-1 : 00 01 10 11
    if(Mode == 1)
    {
        m_Inverter.SetPosInvert(false);
        m_Inverter.SetNegInvert(false);
    }
    else if(Mode == 2)
    {
        m_Inverter.SetPosInvert(false);
        m_Inverter.SetNegInvert(true);
    }
    else if(Mode == 3)
    {
        m_Inverter.SetPosInvert(true);
        m_Inverter.SetNegInvert(false);
    }
    else if(Mode == 4)
    {
        m_Inverter.SetPosInvert(true);
        m_Inverter.SetNegInvert(true);
    }
}

void CSynth12Controller::SetDerectifierMode(int Mode)
{
    // TODO use bitwise ands on Mode-1 : 00 01 10 11
    if(Mode == 1)
    {
        m_Derectifier.SetPosDerectify(false);
        m_Derectifier.SetNegDerectify(false);
    }
    else if(Mode == 2)
    {
        m_Derectifier.SetPosDerectify(false);
        m_Derectifier.SetNegDerectify(true);
    }
    else if(Mode == 3)
    {
        m_Derectifier.SetPosDerectify(true);
        m_Derectifier.SetNegDerectify(false);
    }
    else if(Mode == 4)
    {
        m_Derectifier.SetPosDerectify(true);
        m_Derectifier.SetNegDerectify(true);
    }
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

void CSynth12Controller::OnDistortionDrive(float Drive)
{
    m_Distortion.SetDrive(Drive);
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
        *pDst = m_MasterVolume()*m_Distortion( m_LPFilter( SymmWaveFold( m_Envelope() * m_Derectifier(m_Inverter(m_CarrierWaveTable(m_CarrierPhaseInverter(m_CarrierPhase(m_CarrierPlaybackSpeedMultiplier*m_CarrierPhaseStep()))))), WaveFolder, m_Fold()) ) );
        ++pDst;
    }

    return 0; // zero means ok
}
