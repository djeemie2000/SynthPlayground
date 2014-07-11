#include <cstring>
#include <iostream>
#include "Synth9Controller.h"
#include "ScopeI.h"
#include "SelectableOperator.h"
#include "Pitch.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"
#include "Conversions.h"
#include "SelectableOperatorFactory.h"
#include "MidiNoteConverter.h"


CSynth9Controller::CSynth9Controller(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create())
    , m_Fold(1.0f)
    , m_LPFilter()
    , m_NonLinearShaper()
    , m_Envelope()
    , m_StepSequencer(SamplingFrequency)
    , m_LFO(2, {SamplingFrequency, CSelectableOperatorFactory::Create()})
    , m_NumSamplesGenerator(SamplingFrequency)
    , m_Delay(SamplingFrequency*5, 0.0f)//5 seconds capacity
    , m_MasterVolume()
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.SelectCarrier(0);
    m_Oscillator.SelectModulator(3);
    m_Oscillator.SelectOscillator(0);
    m_LPFilter.SetStages(1);

    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());

    for(auto& LFO : m_LFO)
    {
        LFO.SetFrequency(1);
        LFO.SelectWaveform(0);
    }

    m_MasterVolume.Set(1.0f);//default full volume
}

CSynth9Controller::~CSynth9Controller()
{

}

void CSynth9Controller::OnSync()
{
    m_Oscillator.Sync();
}

void CSynth9Controller::OnNoteOn(ENote Note, EOctave Octave)
{
    //std::cout << "NoteOn" << std::endl;
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Oscillator.Sync();//optional?
    m_Envelope.NoteOn();
}

void CSynth9Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    //std::cout << "NoteOff" << std::endl;
    m_Envelope.NoteOff();
}

void CSynth9Controller::OnCarrier(int Selected)
{
    m_Oscillator.SelectCarrier(Selected);
}

void CSynth9Controller::OnModulator(int Selected)
{
    m_Oscillator.SelectModulator(Selected);
}

void CSynth9Controller::OnOscillator(int Selected)
{
    m_Oscillator.SelectOscillator(Selected);
}

void CSynth9Controller::OnModulatorFrequencyMultiplier(float FrequencyMultiplier)
{
    m_Oscillator.SetModulatorFrequencyMultiplier(FrequencyMultiplier);
}

void CSynth9Controller::OnModulatorPhaseshift(float PhaseShift)
{
    m_Oscillator.SetModulatorPhaseshift(PhaseShift);
}

void CSynth9Controller::OnModulatorAmplitude(float Amplitude)
{
    m_Oscillator.SetModulatorAmplitude(Amplitude);
}

void CSynth9Controller::OnModulatorAmplitudeModAmount(float Amount)
{
    m_Oscillator.SetModulatorAmplitudeModAmount(Amount);
}

void CSynth9Controller::OnWaveFold(float Fold)
{
    m_Fold = Fold;
}

void CSynth9Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
}

void CSynth9Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth9Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CSynth9Controller::OnNonLinearShaperA(float A)
{
    m_NonLinearShaper.SetA(A);
}

void CSynth9Controller::OnNonLinearShaperB(float B)
{
    m_NonLinearShaper.SetB(B);
}

void CSynth9Controller::OnNonLinearShaperPreGain(float PreGain)
{
    m_NonLinearShaper.SetPregain(PreGain);
}

int CSynth9Controller::NumSteps() const
{
    return m_StepSequencer.NumSteps();
}

void CSynth9Controller::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CSynth9Controller::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CSynth9Controller::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CSynth9Controller::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth9Controller::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth9Controller::Start()
{
    //std::printf"StepSequencer Start \r\n");
    m_StepSequencerTicker.Activate(true);
}

void CSynth9Controller::Stop()
{
    //std::printf"StepSequencer Stop \r\n");
    m_StepSequencerTicker.Activate(false);
}

void CSynth9Controller::OnNoteOn(int Note, int , std::uint32_t TimeStamp)
{
    std::cout << "Midi NoteOn : " << Note << std::endl;
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth9Controller::OnNoteOff(int Note, int, std::uint32_t TimeStamp)
{
    std::cout << "Midi NoteOff : " << Note << std::endl;
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth9Controller::OnController(int , int, std::uint32_t)
{
}

void CSynth9Controller::OnPitchbend(int , std::uint32_t )
{
}

void CSynth9Controller::OnUnknown(std::uint32_t)
{
}

void CSynth9Controller::SetLFOFrequency(int Idx, float Frequency)
{
    m_LFO.at(Idx).SetFrequency(Frequency);
}

void CSynth9Controller::SelectLFOWaveform(int Idx, int Selected)
{
    m_LFO.at(Idx).SelectWaveform(Selected);
}

int CSynth9Controller::LFOBankSize() const
{
    return static_cast<int>(m_LFO.size());
}

void CSynth9Controller::OnDelayMilliSeconds(float Delay)
{
    m_NumSamplesGenerator.SetMilliSeconds(Delay);
    m_Delay.SetDelay(m_NumSamplesGenerator());
}

void CSynth9Controller::OnDelayFeedback(float Feedback)
{
    m_Delay.SetFeedback(Feedback);
}

void CSynth9Controller::OnDelayWetDry(float WetDry)
{
    m_Delay.SetWet(WetDry);
}

void CSynth9Controller::OnDelayBypass(bool Bypass)
{
    m_Delay.SetBypass(Bypass);
}

void CSynth9Controller::OnEnvelopeAttack(float AttackMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(AttackMilliSeconds);
    m_Envelope.SetAttackSamples(m_NumSamplesGenerator());
}

void CSynth9Controller::OnEnvelopeRelease(float ReleaseMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(ReleaseMilliSeconds);
    m_Envelope.SetReleaseSamples(m_NumSamplesGenerator());
}

void CSynth9Controller::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}

int CSynth9Controller::OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp)
{
    CSymmetricalOperator<float> Symm;
    CSymmetricalOperator<float> Symm2;
    CWaveFold2<float> Fold;
    Fold.SetFold(m_Fold);
    float MasterVolume = m_MasterVolume();

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

        *pDst = MasterVolume*(m_Delay(m_Envelope()*Symm2(m_LPFilter(Symm(m_Oscillator(m_LFO[0]()), Fold)), m_NonLinearShaper)));
        ++pDst;
    }

    return 0; // zero means ok
}
