#ifndef AUDIOSOURCE2I_H
#define AUDIOSOURCE2I_H

#include <cstdint>

class IAudioSource2
{
public:
    virtual ~IAudioSource2(){}

    /*!
     * \brief OnRead
     * \param Dst buffer to write to
     * \param NumFrames number of frames that is required to be written into buffer
     * \return zero upon success, non-zero error code upon failure
     */
    virtual int OnRead(void *Dst, int NumFrames) =0;
};

#endif // AUDIOSOURCE2I_H
