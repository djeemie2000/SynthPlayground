#include <iostream>
#include <vector>
#include <cstdint>
#include "ReadWavFile.h"

using namespace std;

namespace
{

//TODO move into conversions.h

template<class T>
void SplitStereo(const std::vector<T>& Stereo, std::vector<T>& Left, std::vector<T>& Right)
{
    Left.assign(Stereo.size()/2, 0);
    Right.assign(Stereo.size()/2, 0);
    for(int idx = 0; idx<Stereo.size()/2; ++idx)
    {
        Left[idx] = Stereo[2*idx];
        Right[idx] = Stereo[2*idx+1];
    }
}

void ConvertToFloat(const std::vector<std::int16_t>& In, std::vector<float>& Out)
{
    const float Divider = INT16_MAX;
    for(auto& Src : In)
    {
        Out.push_back(Src/Divider);
    }
}

void ConvertToFloat(const std::vector<std::int8_t>& In, std::vector<float>& Out)
{
    const float Divider = INT8_MAX;
    for(auto& Src : In)
    {
        Out.push_back(Src/Divider);
    }
}

}

class CWavFileReader
{
public:
    CWavFileReader()
    {}

    void Clear()
    {
        m_SamplingFrequency = 0;
        m_Left.clear();
        m_Right.clear();
    }

    bool Read(const std::string& Path)
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
                        ConvertToFloat(Left, m_Left);
                        ConvertToFloat(Right, m_Right);
                        m_SamplingFrequency = SamplingFrequency;
                        Success = true;
                    }
                    else
                    {
                        ConvertToFloat(Data, m_Left);
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
                        ConvertToFloat(Left, m_Left);
                        ConvertToFloat(Right, m_Right);
                        m_SamplingFrequency = SamplingFrequency;
                        Success = true;
                    }
                    else
                    {
                        ConvertToFloat(Data, m_Left);
                        m_SamplingFrequency = SamplingFrequency;
                        Success = true;
                    }
                }
            }
        }

        return Success;
    }

    int GetSamplingFrequency() const
    {
        return m_SamplingFrequency;
    }

    const std::vector<float> GetLeft() const
    {
        return m_Left;
    }

    const std::vector<float> GetRight() const
    {
        return m_Right;
    }
private:
    int m_SamplingFrequency;
    std::vector<float> m_Left;
    std::vector<float> m_Right;
};

int main()
{
    cout << "Hello World!" << endl;

    const std::string Path = "/home/pj/Downloads/FreeDrumKits.net - Krush Sound Kit/U-Radar.wav";
    //const std::string Path = "/home/pj/Downloads/FreeDrumKits.net - Krush Sound Kit/P-Outerspace.wav";

    CWavFileReader Reader;
    if(Reader.Read(Path))
    {
        std::cout << "Read Data " << Path << std::endl;
        std::cout << "fs=" << Reader.GetSamplingFrequency() << std::endl;// << " Ch=" << NumChannels << " Bps=" << BitsPerSample << std::endl;
        std::cout << "Data size=" << Reader.GetLeft().size() << " / " << Reader.GetRight().size() << std::endl;
    }
    else
    {
        std::cout << "Failed to read " << Path << std::endl;
    }

    return 0;
}

