#include <cstring>
#include <iostream>
#include "Synth11Controller.h"
#include "ScopeI.h"
#include "SelectableOperator.h"
#include "Pitch.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"
#include "SelectableOperatorFactory.h"
#include "MidiNoteConverter.h"
#include "Amp.h"

CSynth11Controller::CSynth11Controller(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create())
    , m_Shaper()
    , m_Fold()
    , m_LPFilterCutoff()
    , m_LPFilter()
    , m_NumSamplesGenerator(SamplingFrequency)
    , m_AREnvelope()
    , m_Envelope(4, CADSREnvelope<float>())
    , m_LFO(4, {static_cast<float>(SamplingFrequency), CSelectableOperatorFactory::Create()})
    , m_Modulator(4, CModulatorSigned<float>())
    , m_Distortion()
    , m_MasterVolume()
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.SelectOperator1(0);
    m_Oscillator.SelectOperator2(0);

    m_Fold.Set(0.97f);
    m_LPFilterCutoff.Set(1.0f);

    m_LPFilter.SetStages(1);

    for(auto& LFO : m_LFO)
    {
        LFO.SetFrequency(1);
        LFO.SelectWaveform(3);
    }

    m_MasterVolume.Set(1.0f);//default full volume
}

CSynth11Controller::~CSynth11Controller()
{
}

void CSynth11Controller::OnNoteOn(ENote Note, EOctave Octave)
{
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_AREnvelope.NoteOn();
    for(auto& Envelope : m_Envelope)
    {
        Envelope.NoteOn();
    }
}

void CSynth11Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    m_AREnvelope.NoteOff();
    for(auto& Envelope : m_Envelope)
    {
        Envelope.NoteOff();
    }
}

void CSynth11Controller::SelectOperator1(int Selected)
{
    m_Oscillator.SelectOperator1(Selected);
}

void CSynth11Controller::SelectOperator2(int Selected)
{
    m_Oscillator.SelectOperator2(Selected);
}

void CSynth11Controller::SetMix(float Mix)
{
    m_Oscillator.SetMix(Mix);
}

void CSynth11Controller::SetMixModAmt(float ModAmt)
{
    m_Oscillator.SetMixModAmt(ModAmt);
}

void CSynth11Controller::SetSkew(float Skew)
{
    m_Oscillator.SetSkew(Skew);
}

void CSynth11Controller::SetSkewModAmt(float ModAmt)
{
    m_Oscillator.SetSkewModAmt(ModAmt);
}

void CSynth11Controller::SetShaperStrength(float Strength)
{
    m_Shaper.SetStrength(Strength);
}

void CSynth11Controller::SetShaperPower(int Power)
{
    m_Shaper.SetPower(Power);
}

void CSynth11Controller::SetShaperPreGain(float PreGain)
{
    m_Shaper.SetPreGain(PreGain);
}

void CSynth11Controller::SetInverterMode(int Mode)
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

void CSynth11Controller::SetDerectifierMode(int Mode)
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

void CSynth11Controller::OnWaveFold(float Fold)
{
    m_Fold.Set(Fold);
}

void CSynth11Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
    m_LPFilterCutoff.Set(Parameter);
}

void CSynth11Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth11Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CSynth11Controller::OnNoteOn(int Note, int , std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOn : " << Note << std::endl;
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth11Controller::OnNoteOff(int Note, int, std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOff : " << Note << std::endl;
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth11Controller::OnController(int , int, std::uint32_t)
{
}

void CSynth11Controller::OnPitchbend(int , std::uint32_t )
{
}

void CSynth11Controller::OnUnknown(std::uint32_t)
{
}

void CSynth11Controller::OnEnvelopeAttack(int Idx, float AttackMilliSeconds)
{
    m_Envelope.at(Idx).SetAttackSamples(m_NumSamplesGenerator.SetMilliSeconds(AttackMilliSeconds));
}

void CSynth11Controller::OnEnvelopeDecay(int Idx, float DecayMilliSeconds)
{
    m_Envelope.at(Idx).SetDecaySamples(m_NumSamplesGenerator.SetMilliSeconds(DecayMilliSeconds));
}

void CSynth11Controller::OnEnvelopeSustain(int Idx, float Sustain)
{
    m_Envelope.at(Idx).SetSustain(Sustain);
}

void CSynth11Controller::OnEnvelopeRelease(int Idx, float ReleaseMilliSeconds)
{
    m_Envelope.at(Idx).SetReleaseSamples(m_NumSamplesGenerator.SetMilliSeconds(ReleaseMilliSeconds));
}

void CSynth11Controller::SetLFOFrequency(int Idx, float Frequency)
{
    m_LFO.at(Idx).SetFrequency(Frequency);
}

void CSynth11Controller::SelectLFOWaveform(int Idx, int Selected)
{
    m_LFO.at(Idx).SelectWaveform(Selected);
}

int CSynth11Controller::LFOBankSize() const
{
    return static_cast<int>(m_LFO.size());
}

void CSynth11Controller::OnModAmount(int Modulator, float ModAmt)
{
    if(Modulator==0)
    { // mix
        m_Oscillator.SetMixModAmt(ModAmt);
    }
    else if(Modulator==1)
    {
        m_Oscillator.SetSkewModAmt(ModAmt);
    }
    m_Modulator.at(Modulator).SetModAmount(ModAmt);
}

void CSynth11Controller::OnDistortionDrive(float Drive)
{
    m_Distortion.SetDrive(Drive);
}

void CSynth11Controller::OnEnvelopeAttack(float AttackMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(AttackMilliSeconds);
    m_AREnvelope.SetAttackSamples(m_NumSamplesGenerator());
}

void CSynth11Controller::OnEnvelopeRelease(float ReleaseMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(ReleaseMilliSeconds);
    m_AREnvelope.SetReleaseSamples(m_NumSamplesGenerator());
}

void CSynth11Controller::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}

int CSynth11Controller::OnRead(void *Dst, int NumFrames, std::uint32_t /*TimeStamp*/)
{    
    CSymmetricalOperator<float> SymmWaveFold;
    CWaveFold2<float> WaveFolder;
    CAmp<float> EnvelopeAmp;

    float* pDst = reinterpret_cast<float*>(Dst);
    float* pDstEnd = pDst + NumFrames;

    while(pDst<pDstEnd)
    {
        float ModInMix = m_Envelope[0]();//m_LFO[0]();
        float ModInSkew = m_Envelope[1]();//m_LFO[1]();
        *pDst = m_MasterVolume()*m_Distortion( EnvelopeAmp(m_LPFilter( SymmWaveFold( m_Derectifier(m_Inverter(m_Shaper(m_Oscillator(ModInMix, ModInSkew)))), WaveFolder, m_Modulator[3](m_Fold(), m_Envelope[3]())) , m_Modulator[2](m_LPFilterCutoff(), m_Envelope[2]()) ), m_AREnvelope()) );
        ++pDst;
    }

    return 0; // zero means ok
}
