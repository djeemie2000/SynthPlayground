#ifndef AUDIORENDERERI_H
#define AUDIORENDERERI_H

class IAudioRenderer
{
public:
    virtual ~IAudioRenderer(){}

    virtual int OnWrite(void* Src, int NumFrames) =0;
};

#endif // AUDIORENDERERI_H
