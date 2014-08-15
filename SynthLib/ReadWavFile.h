#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <iostream>

template <typename T>
T read(std::ifstream& stream) {
    T t;
    stream.read((char*)&t, sizeof(T));
    return t;
}

std::string read(std::ifstream& stream, int Size);

bool readWAVHeader(const char* infile, int& SamplingFrequency, int& NumChannels, int& BitsPerSample);

template <typename SampleType>
bool readWAVData(const char* infile, std::vector<SampleType>& values, int& sampleRate, int& channels)
{
    std::ifstream stream(infile, std::ios::binary);
    if(stream.is_open())
    {
        if("RIFF" == read(stream, 4))
        {
            int TotalSize = read<int>(stream);
            if("WAVE" == read(stream, 4)
            && "fmt " == read(stream, 4) // -> fmt chuck starts here
            && 16 == read<int>(stream)// header size
            && 1 == read<short>(stream))//PCM format (1), others not supported
            {
                channels = read<short>(stream);
                sampleRate = read<int>(stream);
                int ByteRate = read<int>(stream);//TODO check  == SampleRate * NumChannels * BitsPerSample/8
                int FrameSize = read<short>(stream);//TODO check == NumChannels * BitsPerSample/8
                int BitsPerSample = read<short>(stream);//TODO should be numChannels * sizeof(SampleType)
                if("data"==read(stream, 4)) // -> data chuck starts here
                {
                    int DataSize = read<int>(stream);
                    int Size = DataSize / sizeof(SampleType);
                    values.assign(Size, SampleType());
                    stream.read(( char*)values.data(), DataSize);

                    return (FrameSize == channels*BitsPerSample/8)
                            && (ByteRate == sampleRate*channels*BitsPerSample/8);
                }
            }
        }

    }

    return false;
}
