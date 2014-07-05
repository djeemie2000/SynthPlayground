#ifndef SCOPECONTROLLER_H
#define SCOPECONTROLLER_H

#include "AudioRendererI.h"
#include "PeriodicSampleGrabberI.h"
#include "PeriodicSampleGrabber.h"

template<class T> class IScope;

class CScopeController : public IAudioRenderer
                        , public IPeriodicSampleGrabber
{
public:
    CScopeController(IScope<float>& Scope);

    int OnWrite(void *Src, int NumFrames) override;

    void OnGrabSize(int GrabSize) override;
    void OnGrabPeriod(int GrabPeriod) override;

private:
    IScope<float>& m_Scope;
    CPeriodicSampleGrabber<float> m_Grabber;
};

#endif // SCOPECONTROLLER_H
