#ifndef PERIODICSAMPLEGRABBERPROXY_H
#define PERIODICSAMPLEGRABBERPROXY_H

#include <memory>
#include "PeriodicSampleGrabberI.h"

class CPeriodicSampleGrabberProxy : public IPeriodicSampleGrabber
{
public:
    CPeriodicSampleGrabberProxy();

    void OnGrabSize(int GrabSize) override;
    void OnGrabPeriod(int GrabPeriod) override;

    void Reset(std::shared_ptr<IPeriodicSampleGrabber> Grabber);

private:
    std::shared_ptr<IPeriodicSampleGrabber> m_Grabber;
};

#endif // PERIODICSAMPLEGRABBERPROXY_H
