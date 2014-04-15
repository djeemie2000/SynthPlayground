#include <fstream>

#include <iostream>

template <typename T>
void write(std::ofstream& stream, const T& t) {
  stream.write((const char*)&t, sizeof(T));
}

template <typename SampleType>
void writeWAVData(const char* outFile, SampleType* buf, size_t bufSize,
                  int sampleRate, int channels)
{
  std::ofstream stream(outFile, std::ios::binary);
  if(!stream.is_open())
  {
      std::cout << "failed to write to " << outFile << std::endl;
      return;
  }

//  std::cout << "ChunckSize=" << 36 + bufSize * channels * sizeof(SampleType) << std::endl
//            << "Subchunk2Size=" << bufSize * channels * sizeof(SampleType) << std::endl
//            << "SampleRate=" << sampleRate << std::endl
//            << "ByteRate=" << sampleRate * channels * sizeof(SampleType)  << std::endl
//            << "BlockAlign=" << channels * sizeof(SampleType) << std::endl
//            << std::endl;


  stream.write("RIFF", 4);
  write<int>(stream, 36 + bufSize * channels * sizeof(SampleType));
  stream.write("WAVE", 4);

  stream.write("fmt ", 4);
  write<int>(stream, 16);
  write<short>(stream, 1);                                        // Format (1 = PCM)
  write<short>(stream, channels);                                 // Channels
  write<int>(stream, sampleRate);                                 // Sample Rate
  write<int>(stream, sampleRate * channels * sizeof(SampleType) ); // Byterate
  write<short>(stream, channels * sizeof(SampleType) );            // Frame size / blockAlign
  write<short>(stream, 8 * sizeof(SampleType));                   // Bits per sample

  stream.write("data", 4);
  write<int>(stream, bufSize * channels * sizeof(SampleType) );//stream.write((const char*)&bufSize, 4);
  stream.write((const char*)buf, bufSize);
}
