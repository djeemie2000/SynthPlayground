#include "periodicsamplegrabberproxy.h"

CPeriodicSampleGrabberProxy::CPeriodicSampleGrabberProxy()
 : m_Grabber()
{
}

void CPeriodicSampleGrabberProxy::OnGrabSize(int GrabSize)
{
    if(m_Grabber)
    {
        m_Grabber->OnGrabSize(GrabSize);
    }
}

void CPeriodicSampleGrabberProxy::OnGrabPeriod(int GrabPeriod)
{
    if(m_Grabber)
    {
        m_Grabber->OnGrabPeriod(GrabPeriod);
    }
}

void CPeriodicSampleGrabberProxy::Reset(std::shared_ptr<IPeriodicSampleGrabber> Grabber)
{
    m_Grabber = Grabber;
}
