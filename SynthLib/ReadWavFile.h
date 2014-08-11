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

std::string read(std::ifstream& stream, int Size)
{
    std::string text;
    for(int idx=0; idx<Size; ++idx)
    {
        char Temp;
        stream.get(Temp);
        text.push_back(Temp);
    }
    return text;
}

bool readWAVHeader(const char* infile, int& sampleRate, int& channels, int& BitSize)
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
                BitSize = BitsPerSample;

                return true;
            }
        }
    }

    return false;
}


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

                    return true;
                }
            }
        }

    }

    return false;
}

//template <typename SampleType>
//void writeWAVData(const char* outFile, SampleType* buf, size_t bufSize,
//                  int sampleRate, int channels)
//{
//  std::ofstream stream(outFile, std::ios::binary);
//  if(!stream.is_open())
//  {
//      std::cout << "failed to write to " << outFile << std::endl;
//      return;
//  }

////  std::cout << "ChunckSize=" << 36 + bufSize * channels * sizeof(SampleType) << std::endl
////            << "Subchunk2Size=" << bufSize * channels * sizeof(SampleType) << std::endl
////            << "SampleRate=" << sampleRate << std::endl
////            << "ByteRate=" << sampleRate * channels * sizeof(SampleType)  << std::endl
////            << "BlockAlign=" << channels * sizeof(SampleType) << std::endl
////            << std::endl;


//  stream.write("RIFF", 4);
//  write<int>(stream, 36 + bufSize * channels * sizeof(SampleType));
//  stream.write("WAVE", 4);

//  stream.write("fmt ", 4);
//  write<int>(stream, 16);
//  write<short>(stream, 1);                                        // Format (1 = PCM)
//  write<short>(stream, channels);                                 // Channels
//  write<int>(stream, sampleRate);                                 // Sample Rate
//  write<int>(stream, sampleRate * channels * sizeof(SampleType) ); // Byterate
//  write<short>(stream, channels * sizeof(SampleType) );            // Frame size / blockAlign
//  write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample

//  stream.write("data", 4);
//  write<int>(stream, bufSize * channels * sizeof(SampleType) );//stream.write((const char*)&bufSize, 4);
//  stream.write((const char*)buf, bufSize);
//}
