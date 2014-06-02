#include <cstring>
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


CSynth8Controller::CSynth8Controller(IScope &Scope, int SamplingFrequency)
    : m_Scope(Scope)
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create(), CSelectableCombinorFactory::Create())
    , m_Fold(1.0f)
    , m_LPFilter()
    , m_NonLinearShaper()
    , m_Envelope()
    , m_StepSequencer(SamplingFrequency)
    , m_LFO1(SamplingFrequency, CSelectableOperatorFactory::Create())
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.Select(0, 0);
    m_Oscillator.Select(1, 0);
    m_Oscillator.SelectCombinor(0);
    m_LPFilter.SetStages(1);

    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());

    m_LFO1.SetFrequency(1);
    m_LFO1.SelectWaveform(0);
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
    //std::printf"NoteOn \r\n");
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Oscillator.Sync();//optional?
    m_Envelope.NoteOn();
}

void CSynth8Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    //std::printf"NoteOff \r\n");
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

int CSynth8Controller::NumSteps() const
{
    return m_StepSequencer.NumSteps();
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

void CSynth8Controller::OnNoteOn(int Note, int)
{
    //std::printf"Midi NoteOn : %d \r\n", Note);
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth8Controller::OnNoteOff(int Note, int)
{
    //std::printf"Midi NoteOff : %d \r\n", Note);
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth8Controller::OnController(int , int)
{
}

void CSynth8Controller::OnPitchbend(int )
{
}

void CSynth8Controller::OnUnknown()
{
}

void CSynth8Controller::SetFrequency(int Idx, float Frequency)
{
    m_LFO1.SetFrequency(Frequency);
}

void CSynth8Controller::SelectWaveform(int Idx, int Selected)
{
    m_LFO1.SelectWaveform(Selected);
}

void CSynth8Controller::OnGrab(int GrabSize)
{
    m_GrabSample = true;
    m_SampleGrabber.OnGrab(GrabSize);
}

std::int64_t CSynth8Controller::OnRead(char *Dst, std::int64_t MaxSize)
{
    //std::printf("OnRead \r\n");


    int MaxReadSize = 512;//1<<10;
    std::size_t Size = MaxSize<MaxReadSize ? MaxSize : MaxReadSize;

    CSymmetricalOperator<float> Symm;
    CSymmetricalOperator<float> Symm2;
    CWaveFold2<float> Fold;
    Fold.SetFold(m_Fold);

    SampleValueType* pDst = reinterpret_cast<SampleValueType*>(Dst);
    SampleValueType* pDstEnd = reinterpret_cast<SampleValueType*>(Dst + Size);


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
        *pDst = (SignedToInt16<float>(m_Envelope()*Symm2(m_LPFilter(Symm(m_Oscillator(m_LFO1()), Fold)), m_NonLinearShaper)));
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
            m_Scope.SetSample(m_SampleGrabber.GetSample());

            m_GrabSample = false;//avoid SetSample() over and over again
        }
    }

    return Size;
}
