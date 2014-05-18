#ifndef SAMPLEGRABBERI_H
#define SAMPLEGRABBERI_H

class ISampleGrabber
{
public:
    virtual ~ISampleGrabber(){}

    virtual void OnGrab(int Size) =0;
};

#endif // SAMPLEGRABBERI_H
