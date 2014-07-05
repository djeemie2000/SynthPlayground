#ifndef PERIODICSAMPLEGRABBERI_H
#define PERIODICSAMPLEGRABBERI_H

class IPeriodicSampleGrabber
{
public:
    virtual ~IPeriodicSampleGrabber(){}

    virtual void OnGrabSize(int GrabSize) =0;
    virtual void OnGrabPeriod(int GrabPeriod) =0;
};

#endif // PERIODICSAMPLEGRABBERI_H
