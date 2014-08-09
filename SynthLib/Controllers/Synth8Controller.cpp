#include <cstring>
#include <iostream>
#include "Synth8Controller.h"
#include "ScopeI.h"
#include "SelectableCombinor.h"
#include "SelectableOperator.h"
#include "Pitch.h"
#include "WaveFolder.h"
#include "SymmetricalOperator.h"
#include "Conversions.h"
#include "SelectableCombinorFactory.h"
#include "SelectableOperatorFactory.h"
#include "MidiNoteConverter.h"


CSynth8Controller::CSynth8Controller(int SamplingFrequency)
    : m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create(), CSelectableCombinorFactory::Create())
    , m_Fold(1.0f)
    , m_LPFilter()
    , m_NonLinearShaper()
    , m_Envelope()
    , m_StepSequencer(SamplingFrequency)
    , m_LFO(2, {static_cast<float>(SamplingFrequency), CSelectableOperatorFactory::Create()})
    , m_NumSamplesGenerator(SamplingFrequency)
    , m_Delay(SamplingFrequency*5, 0.0f)//5 seconds capacity
    , m_MasterVolume()
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.Select(0, 0);
    m_Oscillator.Select(1, 0);
    m_Oscillator.SelectCombinor(0);
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

CSynth8Controller::~CSynth8Controller()
{

}

void CSynth8Controller::OnSync()
{
    m_Oscillator.Sync();
}

void CSynth8Controller::OnNoteOn(ENote Note, EOctave Octave)
{
    //std::cout << "NoteOn" << std::endl;
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Oscillator.Sync();//optional?
    m_Envelope.NoteOn();
}

void CSynth8Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    //std::cout << "NoteOff" << std::endl;
    m_Envelope.NoteOff();
}

void CSynth8Controller::OnCombinor(int Selected)
{
    m_Oscillator.SelectCombinor(Selected);
}

void CSynth8Controller::OnOperator(int Idx, int Selected)
{
    m_Oscillator.Select(Idx, Selected);
}

void CSynth8Controller::OnAmplitude(int Idx, float Amplitude)
{
    m_Oscillator.SetAmplitude(Idx, Amplitude);
}

void CSynth8Controller::OnFrequencyMultiplier(int Idx, float FrequencyMultiplier)
{
    m_Oscillator.SetFrequencyMultiplier(Idx, FrequencyMultiplier);
}

void CSynth8Controller::OnPhaseshift(int Idx, float PhaseShift)
{
    m_Oscillator.SetPhaseShift(Idx, PhaseShift);
}

void CSynth8Controller::OnFold(int Idx, float Fold)
{
    m_Oscillator.SetFold(Idx, Fold);
}

void CSynth8Controller::OnFoldModAmount(int Oscillator, float Amount)
{
    m_Oscillator.SetFoldModAmount(Oscillator, Amount);
}

void CSynth8Controller::OnWaveFold(float Fold)
{
    m_Fold = Fold;
}

void CSynth8Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
}

void CSynth8Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth8Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CSynth8Controller::OnNonLinearShaperA(float A)
{
    m_NonLinearShaper.SetA(A);
}

void CSynth8Controller::OnNonLinearShaperB(float B)
{
    m_NonLinearShaper.SetB(B);
}

void CSynth8Controller::OnNonLinearShaperPreGain(float PreGain)
{
    m_NonLinearShaper.SetPregain(PreGain);
}

int CSynth8Controller::GetMaxNumSteps() const
{
    return m_StepSequencer.GetMaxNumSteps();
}

void CSynth8Controller::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CSynth8Controller::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CSynth8Controller::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CSynth8Controller::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth8Controller::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth8Controller::SetNumSteps(int NumSteps)
{
    m_StepSequencer.SetNumSteps(NumSteps);
}

void CSynth8Controller::Start()
{
    //std::printf"StepSequencer Start \r\n");
    m_StepSequencerTicker.Activate(true);
}

void CSynth8Controller::Stop()
{
    //std::printf"StepSequencer Stop \r\n");
    m_StepSequencerTicker.Activate(false);
}

void CSynth8Controller::OnNoteOn(int Note, int , std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOn : " << Note << std::endl;
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth8Controller::OnNoteOff(int Note, int , std::uint32_t /*TimeStamp*/)
{
    std::cout << "Midi NoteOff : " << Note << std::endl;
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth8Controller::OnController(int , int , std::uint32_t)
{
}

void CSynth8Controller::OnPitchbend(int , std::uint32_t)
{
}

void CSynth8Controller::OnUnknown(std::uint32_t)
{
}

void CSynth8Controller::SetLFOFrequency(int Idx, float Frequency)
{
    m_LFO.at(Idx).SetFrequency(Frequency);
}

void CSynth8Controller::SelectLFOWaveform(int Idx, int Selected)
{
    m_LFO.at(Idx).SelectWaveform(Selected);
}

int CSynth8Controller::LFOBankSize() const
{
    return static_cast<int>(m_LFO.size());
}

void CSynth8Controller::OnDelayMilliSeconds(float Delay)
{
    m_NumSamplesGenerator.SetMilliSeconds(Delay);
    m_Delay.SetDelay(m_NumSamplesGenerator());
}

void CSynth8Controller::OnDelayFeedback(float Feedback)
{
    m_Delay.SetFeedback(Feedback);
}

void CSynth8Controller::OnDelayWetDry(float WetDry)
{
    m_Delay.SetWet(WetDry);
}

void CSynth8Controller::OnDelayBypass(bool Bypass)
{
    m_Delay.SetBypass(Bypass);
}

void CSynth8Controller::OnEnvelopeAttack(float AttackMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(AttackMilliSeconds);
    m_Envelope.SetAttackSamples(m_NumSamplesGenerator());
}

void CSynth8Controller::OnEnvelopeRelease(float ReleaseMilliSeconds)
{
    m_NumSamplesGenerator.SetMilliSeconds(ReleaseMilliSeconds);
    m_Envelope.SetReleaseSamples(m_NumSamplesGenerator());
}

void CSynth8Controller::SetMasterVolume(float Volume)
{
    m_MasterVolume.Set(Volume);
}

int CSynth8Controller::OnRead(void *Dst, int NumFrames, std::uint32_t /*TimeStamp*/)
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

        *pDst = MasterVolume*(m_Delay(m_Envelope()*Symm2(m_LPFilter(Symm(m_Oscillator(m_LFO[0](), m_LFO[1]()), Fold)), m_NonLinearShaper)));
        ++pDst;
    }

    return 0; // zero means ok
}
