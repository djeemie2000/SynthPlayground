#ifndef STEPSEQUENCER2_H
#define STEPSEQUENCER2_H

#include <vector>
#include "Notes.h"
#include "Pitch.h"
#include "PeriodicConstGenerator.h"

template<class T, int N>
class CStepSequencer2
{
public:
    struct SStep
    {
        bool s_IsActive;
        ENote   s_Note;
        EOctave s_Octave;

        SStep()
            : s_IsActive(false)
            , s_Note(ENote::A)
            , s_Octave(EOctave::Octave2)
        {}
    };

    CStepSequencer2(int SamplingFrequency);

    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);

    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);

    void Advance();

    int NumSteps() const;
    int PeriodSamples() const;
    const SStep& CurrentStep() const;

private:
    bool StepExists(int Step) const;

    const int m_SamplingFrequency;
    std::array<SStep, N> m_Steps;
    int m_Step;
    int m_CurrentStep;
    int m_Bpm;
    int m_BarsPerBeat;
};

template<class T, int N>
CStepSequencer2<T,N>::CStepSequencer2(int SamplingFrequency)
 : m_SamplingFrequency(SamplingFrequency)
 , m_Steps()
 , m_Step(0)
 , m_Bpm(120)
 , m_BarsPerBeat(2)
{
    m_Steps.fill(SStep());
}

template<class T, int N>
int CStepSequencer2<T,N>::NumSteps() const
{
    return N;
}

template<class T, int N>
void CStepSequencer2<T,N>::SetActive(int Step, bool IsActive)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_IsActive = IsActive;
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetOctave(int Step, EOctave Octave)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Octave = Octave;
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetNote(int Step, ENote Note)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Note = Note;
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetBeatsPerMinute(int Bpm)
{
    m_Bpm = Bpm;
}

template<class T, int N>
void CStepSequencer2<T,N>::SetBarsPerBeat(int BarsPerBeat)
{
    m_BarsPerBeat = BarsPerBeat;
}

template<class T, int N>
bool CStepSequencer2<T,N>::StepExists(int Step) const
{
    return 0<=Step && Step<N;
}

template<class T, int N>
int CStepSequencer2<T,N>::PeriodSamples() const
{
    return 60 * m_SamplingFrequency / (m_Bpm * m_BarsPerBeat);
}

template<class T, int N>
const typename CStepSequencer2<T,N>::SStep &CStepSequencer2<T,N>::CurrentStep() const
{
    return m_Steps[m_Step];
}

template<class T, int N>
void CStepSequencer2<T,N>::Advance()
{
    m_Step = (m_Step+1)%N;
}

#endif // STEPSEQUENCER2_H
