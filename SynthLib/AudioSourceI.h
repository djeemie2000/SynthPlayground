#ifndef AUDIOSOURCEI_H
#define AUDIOSOURCEI_H

#include <cstdint>

class IAudioSource
{
public:
    virtual ~IAudioSource(){}

    virtual std::int64_t OnRead(char *Dst, std::int64_t MaxSize) =0;
};

#endif // AUDIOSOURCEI_H
