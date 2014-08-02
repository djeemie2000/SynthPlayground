#ifndef BPMPERIOD_H
#define BPMPERIOD_H

class CBpmPeriod
{
public:
    CBpmPeriod(int SamplingFrequency)
     : m_SamplingFrequency(SamplingFrequency)
     , m_Bpm(120)
     , m_BarsPerBeat(2)
    {}

    void SetBeatsPerMinute(int Bpm)
    {
        m_Bpm = Bpm;
    }

    void SetBarsPerBeat(int BarsPerBeat)
    {
        m_BarsPerBeat = BarsPerBeat;
    }

    int PeriodSamples() const
    {
        return 60 * m_SamplingFrequency / ( m_Bpm * m_BarsPerBeat );
    }

private:
    const int m_SamplingFrequency;
    int m_Bpm;
    int m_BarsPerBeat;
};

#endif // BPMPERIOD_H
