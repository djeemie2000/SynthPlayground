#ifndef WAVETABLE_H
#define WAVETABLE_H

#include <vector>

template<class DataType, class PhaseType>
class CWaveTable
{
public:
    CWaveTable(const std::vector<DataType>& Table, PhaseType SamplingFrequency)
     : m_WaveTable(Table)
     , m_SamplingFrequency(SamplingFrequency)
     , m_Size(Table.size())
    {
        // make sure no bad things happen due to float rounding of the phase
        m_WaveTable.push_back(m_WaveTable.back());
    }

    PhaseType GetSamplingFrequency() const
    {
        return m_SamplingFrequency;
    }

    int GetSize() const
    {
        return m_Size;
    }

    DataType operator()(PhaseType Phase) const
    {
        // Phase is in [0,1] range, representing the position of the returned sample
        // phase is not checked for being in range!
        return m_WaveTable[ int(Phase*m_Size) ];
    }

private:
    std::vector<DataType> m_WaveTable;
    PhaseType m_SamplingFrequency;
    int m_Size;
};

template<class PhaseType>
class CWaveTablePhaseStep
{
public:
    CWaveTablePhaseStep(PhaseType WaveTableSamplingFrequency, int WaveTableSize, PhaseType SamplingFrequency)
     : m_WaveTableSamplingFrequency(WaveTableSamplingFrequency)
     , m_WaveTableSize(WaveTableSize)
     , m_SamplingFrequency(SamplingFrequency)
    {}

    void SetPlaybackSpeed(PhaseType PlaybackSpeed)
    {
        // 1 corresponds to original speed, >1 is faster, <1 is slower
        m_Step = (PlaybackSpeed *  m_WaveTableSamplingFrequency) / (m_SamplingFrequency * m_WaveTableSize);
        // TODO perhaps can be rewritten as m_Step = m_Coeff * PlaybackSpeed
    }

    PhaseType operator()() const
    {
        return m_Step;
    }

private:
    PhaseType m_WaveTableSamplingFrequency;
    int m_WaveTableSize;
    PhaseType m_SamplingFrequency;
    PhaseType m_Step;
};

#endif // WAVETABLE_H
