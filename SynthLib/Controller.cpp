#include <cstring>
#include "Controller.h"
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


CSynth7Controller::CSynth7Controller(IScope &Scope, int SamplingFrequency)
    : m_Scope(Scope)
    , m_GrabSample(false)
    , m_SampleGrabber()
    , m_Oscillator(SamplingFrequency, CSelectableOperatorFactory::Create(), CSelectableCombinorFactory::Create())
    , m_Fold(1.0f)
    , m_Fx()
    , m_LPFilter()
    , m_NonLinearShaper()
    , m_Envelope()
    , m_StepSequencer(SamplingFrequency)
{
    m_Oscillator.SetFrequency(CPitch()(ENote::A, EOctave::Octave2));
    m_Oscillator.Select(0, 0);
    m_Oscillator.Select(1, 0);
    m_Oscillator.SelectCombinor(0);
    m_LPFilter.SetStages(1);

    m_StepSequencer.SetBeatsPerMinute(120);
    m_StepSequencer.SetBarsPerBeat(2);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

CSynth7Controller::~CSynth7Controller()
{

}

void CSynth7Controller::OnSync()
{
    m_Oscillator.Sync();
}

void CSynth7Controller::OnNoteOn(ENote Note, EOctave Octave)
{
    std::printf("NoteOn \r\n");
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Oscillator.Sync();//optional?
    m_Envelope.NoteOn();
}

void CSynth7Controller::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    std::printf("NoteOff \r\n");
    m_Envelope.NoteOff();
}

void CSynth7Controller::OnCombinor(int Selected)
{
    m_Oscillator.SelectCombinor(Selected);
}

void CSynth7Controller::OnOperator(int Idx, int Selected)
{
    m_Oscillator.Select(Idx, Selected);
}

void CSynth7Controller::OnAmplitude(int Idx, float Amplitude)
{
    m_Oscillator.SetAmplitude(Idx, Amplitude);
}

void CSynth7Controller::OnFrequencyMultiplier(int Idx, float FrequencyMultiplier)
{
    m_Oscillator.SetFrequencyMultiplier(Idx, FrequencyMultiplier);
}

void CSynth7Controller::OnPhaseshift(int Idx, float PhaseShift)
{
    m_Oscillator.SetPhaseShift(Idx, PhaseShift);
}

void CSynth7Controller::OnWaveFold(float Fold)
{
    m_Fold = Fold;
}

void CSynth7Controller::OnLPFilterCutoff(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
}

void CSynth7Controller::OnLPFilterPoles(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CSynth7Controller::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CSynth7Controller::OnNonLinearShaperA(float A)
{
    m_NonLinearShaper.SetA(A);
}

void CSynth7Controller::OnNonLinearShaperB(float B)
{
    m_NonLinearShaper.SetB(B);
}

void CSynth7Controller::OnNonLinearShaperPreGain(float PreGain)
{
    m_NonLinearShaper.SetPregain(PreGain);
}

void CSynth7Controller::OnBitCrusherDepth(int Depth)
{
    m_Fx.SetBitCrusherDepth(Depth);
}

void CSynth7Controller::OnSampleAndHoldPeriod(int Period)
{
    m_Fx.SetSampleAndHoldPeriod(Period);
}

void CSynth7Controller::OnRipplerStrength(int Strength)
{
    m_Fx.SetRipplerStrength(Strength);
}

int CSynth7Controller::NumSteps() const
{
    return m_StepSequencer.NumSteps();
}

void CSynth7Controller::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CSynth7Controller::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CSynth7Controller::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CSynth7Controller::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth7Controller::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CSynth7Controller::Start()
{
    std::printf("StepSequencer Start \r\n");
    m_StepSequencerTicker.Activate(true);
}

void CSynth7Controller::Stop()
{
    std::printf("StepSequencer Stop \r\n");
    m_StepSequencerTicker.Activate(false);
}

void CSynth7Controller::OnNoteOn(int Note, int)
{
    std::printf("Midi NoteOn : %d \r\n", Note);
    OnNoteOn(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth7Controller::OnNoteOff(int Note, int)
{
    std::printf("Midi NoteOff : %d \r\n", Note);
    OnNoteOff(CMidiNoteConverter().ToNote(Note), CMidiNoteConverter().ToOctave(Note));
}

void CSynth7Controller::OnController(int , int)
{
}

void CSynth7Controller::OnPitchbend(int )
{
}

void CSynth7Controller::OnUnknown()
{
}

void CSynth7Controller::OnGrab(int GrabSize)
{
    m_GrabSample = true;
    m_SampleGrabber.OnGrab(GrabSize);
}

std::int64_t CSynth7Controller::OnRead(char *Dst, std::int64_t MaxSize)
{
    std::printf("OnRead \r\n");


    int MaxReadSize = 1<<13;
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
        *pDst = m_Fx(SignedToInt16<float>(m_Envelope()*Symm2(m_LPFilter(Symm(m_Oscillator(), Fold)), m_NonLinearShaper)));
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
