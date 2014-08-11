#include "WavFileReader.h"
#include "Conversions.h"

namespace
{

void ConvertInt16ToFloat(const std::vector<std::int16_t>& In, std::vector<float>& Out)
{
    Out.clear();
    const float Divider = INT16_MAX;
    for(auto& Src : In)
    {
        Out.push_back(Src/Divider);
    }
}

void ConvertInt8ToFloat(const std::vector<std::int8_t>& In, std::vector<float>& Out)
{
    Out.clear();
    const float Divider = INT8_MAX;
    for(auto& Src : In)
    {
        Out.push_back(Src/Divider);
    }
}

}

CWavFileReader::CWavFileReader()
 : m_SamplingFrequency(0)
 , m_Left()
 , m_Right()
{
    Clear();
}

void CWavFileReader::Clear()
{
    m_SamplingFrequency = 0;
    m_Left.clear();
    m_Right.clear();
}

bool CWavFileReader::Read(const std::string &Path)
{
    Clear();

    bool Success = false;
    int SamplingFrequency = 0;
    int NumChannels = 0;
    int BitsPerSample = 0;
    if(readWAVHeader(Path.c_str(), SamplingFrequency, NumChannels, BitsPerSample))
    {
        if(BitsPerSample==16)
        {
            std::vector<std::int16_t> Data;
            if(readWAVData(Path.c_str(), Data, SamplingFrequency, NumChannels))
            {
                if(NumChannels==2)
                {
                    std::vector<std::int16_t> Left;
                    std::vector<std::int16_t> Right;
                    SplitStereo(Data, Left, Right);
                    ConvertInt16ToFloat(Left, m_Left);
                    ConvertInt16ToFloat(Right, m_Right);
                    m_SamplingFrequency = SamplingFrequency;
                    Success = true;
                }
                else
                {
                    ConvertInt16ToFloat(Data, m_Left);
                    m_SamplingFrequency = SamplingFrequency;
                    Success = true;
                }
            }
        }
        else if(BitsPerSample==8)
        {
            std::vector<std::int8_t> Data;
            if(readWAVData(Path.c_str(), Data, SamplingFrequency, NumChannels))
            {
                if(NumChannels==2)
                {
                    std::vector<std::int8_t> Left;
                    std::vector<std::int8_t> Right;
                    SplitStereo(Data, Left, Right);
                    ConvertInt8ToFloat(Left, m_Left);
                    ConvertInt8ToFloat(Right, m_Right);
                    m_SamplingFrequency = SamplingFrequency;
                    Success = true;
                }
                else
                {
                    ConvertInt8ToFloat(Data, m_Left);
                    m_SamplingFrequency = SamplingFrequency;
                    Success = true;
                }
            }
        }
    }

    return Success;
}

int CWavFileReader::GetSamplingFrequency() const
{
    return m_SamplingFrequency;
}

const std::vector<float> CWavFileReader::GetLeft() const
{
    return m_Left;
}

const std::vector<float> CWavFileReader::GetRight() const
{
    return m_Right;
}
