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
    CStepSequencer2(int SamplingFrequency);

    int NumSteps() const;
    bool IsRunning() const;

    void SetActive(int Step, bool IsActive);
    void SetOctave(int Step, EOctave Octave);
    void SetNote(int Step, ENote Note);

    void SetBeatsPerMinute(int Bpm);
    void SetBarsPerBeat(int BarsPerBeat);

    void Start();
    void Stop();

    CPeriodicConstGenerator<T,N>& Amplitude()   {   return m_AmplitudeGenerator;    }
    CPeriodicConstGenerator<T,N>& Frequency()   {   return m_FrequencyGenerator;    }

private:
    bool StepExists(int Step) const;
    int PeriodSamples() const;

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

    const int m_SamplingFrequency;
    std::array<SStep, N> m_Steps;
    bool m_IsRunning;
    int m_Bpm;
    int m_BarsPerBeat;

    CPeriodicConstGenerator<T,N> m_AmplitudeGenerator;
    CPeriodicConstGenerator<T,N> m_FrequencyGenerator;
};

template<class T, int N>
CStepSequencer2<T,N>::CStepSequencer2(int SamplingFrequency)
 : m_SamplingFrequency(SamplingFrequency)
 , m_Steps()
 , m_IsRunning(false)
 , m_Bpm(120)
 , m_BarsPerBeat(2)
{
    // consistent initial state:
    m_AmplitudeGenerator.SetPeriod(PeriodSamples());
    m_FrequencyGenerator.SetPeriod(PeriodSamples());

    m_Steps.fill(SStep());
    for(int Step = 0; Step<m_Steps.size(); ++Step)
    {
        m_AmplitudeGenerator.SetValue(Step, m_Steps[Step].s_IsActive?0:1);
        m_FrequencyGenerator.SetValue(Step, CPitch()(m_Steps[Step].s_Note, m_Steps[Step].s_Octave));
    }
}

template<class T, int N>
int CStepSequencer2<T,N>::NumSteps() const
{
    return N;
}

template<class T, int N>
bool CStepSequencer2<T,N>::IsRunning() const
{
    return m_IsRunning;
}

template<class T, int N>
void CStepSequencer2<T,N>::SetActive(int Step, bool IsActive)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_IsActive = IsActive;
        m_AmplitudeGenerator.SetValue(Step, IsActive?0:1);
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetOctave(int Step, EOctave Octave)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Octave = Octave;
        m_FrequencyGenerator.SetValue(Step, CPitch()(m_Steps[Step].s_Note, Octave));
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetNote(int Step, ENote Note)
{
    if(StepExists(Step))
    {
        m_Steps[Step].s_Note = Note;
        m_FrequencyGenerator.SetValue(Step, CPitch()(Note, m_Steps[Step].s_Octave));
    }
}

template<class T, int N>
void CStepSequencer2<T,N>::SetBeatsPerMinute(int Bpm)
{
    m_Bpm = Bpm;
    m_AmplitudeGenerator.SetPeriod(PeriodSamples());
    m_FrequencyGenerator.SetPeriod(PeriodSamples());
}

template<class T, int N>
void CStepSequencer2<T,N>::SetBarsPerBeat(int BarsPerBeat)
{
    m_BarsPerBeat = BarsPerBeat;
    m_AmplitudeGenerator.SetPeriod(PeriodSamples());
    m_FrequencyGenerator.SetPeriod(PeriodSamples());
}

template<class T, int N>
void CStepSequencer2<T,N>::Start()
{
    m_IsRunning = true;
}

template<class T, int N>
void CStepSequencer2<T,N>::Stop()
{
    m_IsRunning = false;
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


#endif // STEPSEQUENCER2_H
