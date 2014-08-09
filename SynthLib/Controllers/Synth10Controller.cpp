#include "Synth10Controller.h"

#include <cstring>
#include <iostream>
#include "Synth10Controller.h"
#include "ScopeI.h"
#include "SelectableOperator.h"
#include "Pitch.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"
#include "Conversions.h"
#include "SelectableOperatorFactory.h"
#include "MidiNoteConverter.h"


CSynth10Controller::CSynth10Controller(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create())
    , m_Shaper()
    , m_LPFilter()
    , m_Envelope()
    , m_LFO(3, {static_cast<float>(SamplingFrequency), CSelectableOperatorFactory::Create()})
    , m_StepSequencer(SamplingFrequency)
    , m_Distortion()
    , m_NumSamplesGenerator(SamplingFrequency)
    , m_Delay(SamplingFrequency*5, 0.0f)//5 seconds capacity
    , m_MasterVolume()
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.SelectOperator1(0);
    m_Oscillator.SelectOperator2(0);

    m_LPFilter.SetStages(1);

    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());

    for(auto& LFO : m_LFO)
    {
        LFO.SetFrequency(1);
        LFO.SelectWaveform(3);
    }

    m_MasterVolume.Set(1.0f);//default full volume
}

CSynth10Controller::~CSynth10Controller()
{

}


void CSynth10Controller::OnNoteOn(ENote Note, EOctave Octave)
{
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Envelope.NoteOn();
}

void CSynth10Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    m_Envelope.NoteOff();
}

void CSynth10Controller::SelectOperator1(int Selected)
{
    m_Oscillator.SelectOperator1(Selected);
}

void CSynth10Controller::SelectOperator2(int Selected)
{
    m_Oscillator.SelectOperator2(Selected);
}

void CSynth10Controller::SetMix(float Mix)
{
    m_Oscillator.SetMix(Mix);
}

void CSynth10Controller::SetMixModAmt(float ModAmt)
{
    m_Oscillator.SetMixModAmt(ModAmt);
}

void CSynth10Controller::SetSkew(float Skew)
{
    m_Oscillator.SetSkew(Skew);
}

void CSynth10Controller::SetSkewModAmt(float ModAmt)
{
    m_Oscillator.SetSkewModAmt(ModAmt);
}

void CSynth10Controller::SetShaperStrength(float Strength)
{
    m_Shaper.SetStrength(Strength);
}

void CSynth10Controller::SetShaperPower(int Power)
{
    m_Shaper.SetPower(Power);
}

void CSynth10Controller::SetShaperPreGain(float PreGain)
{
    m_Shaper.SetPreGain(PreGain);
}

void CSynth10Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
}

void CSynth10Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth10Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

int CSynth10Controller::GetMaxNumSteps() const
{
    return m_StepSequencer.GetMaxNumSteps();
}

void CSynth10Controller::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CSynth10Controller::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CSynth10Controller::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CSynth10Controller::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth10Controller::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth10Controller::SetNumSteps(int NumSteps)
{
    m_StepSequencer.SetNumSteps(NumSteps);
}

void CSynth10Controller::Start()
{
    //std::printf"StepSequencer Start \r\n");
    m_StepSequencerTicker.Activate(true);
}

void CSynth10Controller::Stop()
{
    //std::printf"StepSequencer Stop \r\n");
    m_StepSequencerTicker.Activate(false);
}

void CSynth10Controller::OnNoteOn(int Note, int , std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOn : " << Note << std::endl;
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth10Controller::OnNoteOff(int Note, int, std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOff : " << Note << std::endl;
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth10Controller::OnController(int , int, std::uint32_t)
{
}

void CSynth10Controller::OnPitchbend(int , std::uint32_t )
{
}

void CSynth10Controller::OnUnknown(std::uint32_t)
{
}

void CSynth10Controller::SetLFOFrequency(int Idx, float Frequency)
{
    m_LFO.at(Idx).SetFrequency(Frequency);
}

void CSynth10Controller::SelectLFOWaveform(int Idx, int Selected)
{
    m_LFO.at(Idx).SelectWaveform(Selected);
}

int CSynth10Controller::LFOBankSize() const
{
    return static_cast<int>(m_LFO.size());
}

void CSynth10Controller::OnDistortionDrive(float Drive)
{
    m_Distortion.SetDrive(Drive);
}

void CSynth10Controller::OnDelayMilliSeconds(float Delay)
{
    m_NumSamplesGenerator.SetMilliSeconds(Delay);
    m_Delay.SetDelay(m_NumSamplesGenerator());
}

void CSynth10Controller::OnDelayFeedback(float Feedback)
{
    m_Delay.SetFeedback(Feedback);
}

void CSynth10Controller::OnDelayWetDry(float WetDry)
{
    m_Delay.SetWet(WetDry);
}

void CSynth10Controller::OnDelayBypass(bool Bypass)
{
    m_Delay.SetBypass(Bypass);
}

void CSynth10Controller::OnEnvelopeAttack(float AttackMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(AttackMilliSeconds);
    m_Envelope.SetAttackSamples(m_NumSamplesGenerator());
}

void CSynth10Controller::OnEnvelopeRelease(float ReleaseMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(ReleaseMilliSeconds);
    m_Envelope.SetReleaseSamples(m_NumSamplesGenerator());
}

void CSynth10Controller::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}

int CSynth10Controller::OnRead(void *Dst, int NumFrames, std::uint32_t /*TimeStamp*/)
{    
    float* pDst = reinterpret_cast<float*>(Dst);
    float* pDstEnd = pDst + NumFrames;

    while(pDst<pDstEnd)
    {
        if(m_StepSequencerTicker())
        {
            // note off previous step, advance to next step and apply!
            if(m_StepSequencer.CurrentStep().s_IsActive)
            {
                OnNoteOff(m_StepSequencer.CurrentStep().s_Note, m_StepSequencer.CurrentStep().s_Octave);
            }
            m_StepSequencer.Advance();
            if(m_StepSequencer.CurrentStep().s_IsActive)
            {
                OnNoteOn(m_StepSequencer.CurrentStep().s_Note, m_StepSequencer.CurrentStep().s_Octave);
            }
        }

        *pDst = m_MasterVolume()*m_Delay(m_Distortion( m_Envelope()*m_LPFilter( m_Shaper(m_Oscillator(m_LFO[0](), m_LFO[1]())) ) ));
        ++pDst;
    }

    return 0; // zero means ok
}
