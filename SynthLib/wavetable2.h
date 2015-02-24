#ifndef WAVETABLE2
#define WAVETABLE2

#include <vector>

namespace wt2
{

template<class SrcType, class DstType>
class CConvertWaveTableData
{
public:
    DstType Convert(SrcType Src)
    {
        return Src;
    }
};

template<>
class CConvertWaveTableData<std::uint8_t, float>
{
public:

    float Convert(std::uint8_t Src)
    {
        return (Src-128)/128.0f;
    }
};

template<class DataType, class PhaseType, class PlaybackType>
class CWaveTablePlayer
{
public:
    CWaveTablePlayer()
        : m_Data()
        , m_Size(0)
    {}

    void SetWaveTable(const DataType* WaveTableData, int WaveTableSize)
    {
        m_Data.assign(WaveTableSize+1, 0);
        m_Size = WaveTableSize;
        for(int idx = 0; idx<WaveTableSize; ++idx)
        {
            m_Data[idx] = CConvertWaveTableData<DataType, PlaybackType>().Convert(WaveTableData[idx]);
        }
    }

    PlaybackType operator()(PhaseType Phase, int Begin, int Length)
    {
        // Phase is [-1,+1]
        int Index = (Begin + Length*(1+Phase)/2);
        return m_Data[Index%m_Size];
    }

private:
    std::vector<PlaybackType> m_Data;
    int m_Size;
};

template<class DataType, class PhaseType, class PlaybackType>
class CWaveTableManager
{
public:
    CWaveTableManager(const DataType* WaveTableData, int WaveTableSize, int SingleWaveSize)
     : m_Player()
     , m_WaveTableSize(WaveTableSize)
     , m_SingleWaveSize(SingleWaveSize)
    {
        m_Player.SetWaveTable(WaveTableData, WaveTableSize);
    }

    PlaybackType operator()(PhaseType Phase, PhaseType Begin, PhaseType Length)
    {
        int NumSingleWaves = m_WaveTableSize/m_SingleWaveSize;

        // Begin [0,1] to nearest SingleWave begin (at SingleWaveSize multiple)
        int BeginSamples = int(Begin*NumSingleWaves)*m_SingleWaveSize;

        // Length [0,1] to nearest SingleWaveSize multiple
        int LengthSamples = int(Length*NumSingleWaves)*m_SingleWaveSize;
        if(LengthSamples==0)
        {
            LengthSamples = m_SingleWaveSize;
        }

        return m_Player(Phase, BeginSamples, LengthSamples);
    }

    PhaseType GetDefaultBegin() const
    {
        return 0;
    }

    PhaseType GetDefaultLength() const
    {
        return PhaseType(1)/GetNumSingleWaves();
    }

private:
    int GetNumSingleWaves() const
    {
        return m_WaveTableSize/m_SingleWaveSize;
    }

    CWaveTablePlayer<DataType, PhaseType, PlaybackType> m_Player;
    int m_WaveTableSize;
    int m_SingleWaveSize;
};

}//wt2

#endif // WAVETABLE2
