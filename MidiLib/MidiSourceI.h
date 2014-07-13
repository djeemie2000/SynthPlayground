#ifndef MIDISOURCEI_H
#define MIDISOURCEI_H

#include <cstdint>

class IMidiSource
{
public:
    virtual ~IMidiSource(){}

    /*!
     * \brief OnRead
     * \param Dst buffer to write to
     * \param NumFrames number of frames that is required to be written into buffer
     * \return zero upon success, non-zero error code upon failure
     */
    virtual int OnRead(void *Dst, int NumFrames, std::uint32_t TimeStamp) =0;
};

#endif // MIDISOURCEI_H
