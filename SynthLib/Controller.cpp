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


CController::CController(IScope &Scope, int SamplingFrequency)
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
}

CController::~CController()
{

}

void CController::OnPlay()
{
}

void CController::OnStop()
{
}

void CController::OnSync()
{
    m_Oscillator.Sync();
}

void CController::OnNoteOn(ENote Note, EOctave Octave)
{
    m_Oscillator.SetFrequency(CPitch()(Note, Octave));
    m_Oscillator.Sync();//optional?
    m_Envelope.NoteOn();
}

void CController::OnNoteOff(ENote /*Note*/, EOctave /*Octave*/)
{
    m_Envelope.NoteOff();
}

void CController::OnCombinor(int Selected)
{
    m_Oscillator.SelectCombinor(Selected);
}

void CController::OnOperator(int Idx, int Selected)
{
    m_Oscillator.Select(Idx, Selected);
}

void CController::OnAmplitude(int Idx, float Amplitude)
{
    m_Oscillator.SetAmplitude(Idx, Amplitude);
}

void CController::OnFrequencyMultiplier(int Idx, float FrequencyMultiplier)
{
    m_Oscillator.SetFrequencyMultiplier(Idx, FrequencyMultiplier);
}

void CController::OnPhaseshift(int Idx, float PhaseShift)
{
    m_Oscillator.SetPhaseShift(Idx, PhaseShift);
}

void CController::OnWaveFold(float Fold)
{
    m_Fold = Fold;
}

void CController::OnLPFilterParameter(float Parameter)
{
    m_LPFilter.SetParameter(Parameter);
}

void CController::OnLPFilterStages(int Stages)
{
    m_LPFilter.SetStages(Stages);
}

void CController::OnLPFilterFeedback(float Feedback)
{
    m_LPFilter.SetFeedback(Feedback);
}

void CController::OnNonLinearShaperA(float A)
{
    m_NonLinearShaper.SetA(A);
}

void CController::OnNonLinearShaperB(float B)
{
    m_NonLinearShaper.SetB(B);
}

void CController::OnNonLinearShaperPreGain(float PreGain)
{
    m_NonLinearShaper.SetPregain(PreGain);
}

void CController::OnBitCrusherDepth(int Depth)
{
    m_Fx.SetBitCrusherDepth(Depth);
}

void CController::OnSampleAndHoldPeriod(int Period)
{
    m_Fx.SetSampleAndHoldPeriod(Period);
}

void CController::OnRipplerStrength(int Strength)
{
    m_Fx.SetRipplerStrength(Strength);
}

int CController::NumSteps() const
{
    return m_StepSequencer.NumSteps();
}

void CController::SetActive(int Step, bool IsActive)
{
    m_StepSequencer.SetActive(Step, IsActive);
}

void CController::SetOctave(int Step, EOctave Octave)
{
    m_StepSequencer.SetOctave(Step, Octave);
}

void CController::SetNote(int Step, ENote Note)
{
    m_StepSequencer.SetNote(Step, Note);
}

void CController::SetBeatsPerMinute(int Bpm)
{
    m_StepSequencer.SetBeatsPerMinute(Bpm);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CController::SetBarsPerBeat(int BarsPerBeat)
{
    m_StepSequencer.SetBarsPerBeat(BarsPerBeat);
    m_StepSequencerTicker.SetPeriod(m_StepSequencer.PeriodSamples());
}

void CController::Start()
{
    m_StepSequencerTicker.Activate(true);
}

void CController::Stop()
{
    m_StepSequencerTicker.Activate(false);
}

void CController::OnGrab(int GrabSize)
{
    m_GrabSample = true;
    m_SampleGrabber.OnGrab(GrabSize);
}

std::int64_t CController::OnRead(char *Dst, std::int64_t MaxSize)
{
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
