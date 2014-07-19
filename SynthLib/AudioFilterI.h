#ifndef AUDIOFILTERI_H
#define AUDIOFILTERI_H

#include <cstdint>

class IAudioFilter
{
public:
    virtual ~IAudioFilter(){}

    /*!
     * \brief OnUpdate
     * \param Src the source buffer to read from
     * \param Dst the destination buffer to write to
     * \param NumFrames the number of frames to process
     * \param TimeStamp the timestamp (in frames)
     * \return zero upon success, non-zero upon failure
     */
    virtual int OnProcess(void* Src, void* Dst, int NumFrames, std::uint32_t TimeStamp) =0;
};

#endif // AUDIOFILTERI_H
