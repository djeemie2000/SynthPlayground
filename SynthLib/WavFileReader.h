#ifndef WAVFILEREADER_H
#define WAVFILEREADER_H

#include <vector>
#include "ReadWavFile.h"

class CWavFileReader
{
public:
    CWavFileReader();

    void Clear();
    bool Read(const std::string& Path);
    int GetSamplingFrequency() const;
    int GetSize() const;
    const std::vector<float> GetLeft() const;
    const std::vector<float> GetRight() const;

private:
    int m_SamplingFrequency;
    std::vector<float> m_Left;
    std::vector<float> m_Right;
};

#endif // WAVFILEREADER_H
