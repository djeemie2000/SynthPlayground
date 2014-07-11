#ifndef AUDIORENDERERI_H
#define AUDIORENDERERI_H

#include <cstdint>

class IAudioRenderer
{
public:
    virtual ~IAudioRenderer(){}

    virtual int OnWrite(void* Src, int NumFrames, std::uint32_t TimeStamp) =0;
};

#endif // AUDIORENDERERI_H
