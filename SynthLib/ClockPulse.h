#ifndef CLOCKPULSE_H
#define CLOCKPULSE_H

#include "PhaseGenerator.h"
#include "PhaseStep.h"
#include "SquareWave.h"

template<class T>
class CClockPulseIn
{
public:
    CClockPulseIn()
     : m_Prev()
    {}

    bool RisingEdge(T ClockPulse)
    {
        bool Edge = (m_Prev<0 && 0<ClockPulse);
        m_Prev = ClockPulse;
        return Edge;
    }

    bool FallingEdge(T ClockPulse)
    {
        bool Edge = (0<m_Prev<0 && ClockPulse<0);
        m_Prev = ClockPulse;
        return Edge;
    }

    bool AnyEdge(T ClockPulse)
    {
        bool Edge = ((m_Prev<0) != (0<ClockPulse));
        m_Prev = ClockPulse;
        return Edge;
    }

private:
    T m_Prev;
};

template<class T>
class CClockPulseOut
{
public:
    CClockPulseOut(int SamplingFrequency)
     : m_Bpm(120)
     , m_Bpb(1)
     , m_SubDivision(128)
     , m_PhaseStep(SamplingFrequency)
     , m_PhaseAccumulator()
    {
        SetFrequency(CalcFrequency());
    }

    void SetFrequency(T Frequency)
    {
        m_PhaseStep.SetFrequency(Frequency);
    }

    void SetBpm(int Bpm)
    {
        m_Bpm = Bpm;
        SetFrequency(CalcFrequency());
    }

    void SetBpb(int Bpb)
    {
        m_Bpb = Bpb;
        SetFrequency(CalcFrequency());
    }

    void SetSubDivision(int SubDivision)
    {
        m_SubDivision = SubDivision;
        SetFrequency(CalcFrequency());
    }

    T operator()()
    {
        // clock pulse is a square pulse with 50% duty cycle
        // where the rising edge indicates a new clock cycle
        return 0<m_PhaseAccumulator(m_PhaseStep()) ? -1 : 1;
    }

private:
    T CalcFrequency()
    {
        return m_Bpm * m_Bpb * m_SubDivision / static_cast<T>(60); // /60 to convert bpm to bps
    }

    int m_Bpm;
    int m_Bpb;
    int m_SubDivision;

    CPhaseStep<T> m_PhaseStep;
    CPhaseAccumulator<T> m_PhaseAccumulator;
};

#endif // CLOCKPULSE_H
