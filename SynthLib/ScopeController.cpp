//#include <iostream>
#include "ScopeController.h"
#include "ScopeI.h"

CScopeController::CScopeController(IScope<float> &Scope)
 : m_Scope(Scope)
 , m_Grabber()
{
    const int GrabSize = 1024;
    m_Grabber.SetGrabPeriod(32*GrabSize);
    m_Grabber.SetGrabSize(GrabSize);
}

int CScopeController::OnWrite(void *Src, int NumFrames)
{
    if(Src)
    {
        float* SourceData = reinterpret_cast<float*>(Src);
        if(m_Grabber.OnRead(SourceData, NumFrames))
        {
            m_Scope.SetSample(m_Grabber.GetGrabbedSample());
            //std::cout << "Processing " << NumFrames << " frames, grabbed sample of " << m_Grabber.GetGrabbedSample().size() << std::endl;
        }
    }
    return 0;//return 0 if oks
}

void CScopeController::OnGrabSize(int GrabSize)
{
    m_Grabber.SetGrabSize(GrabSize);
}

void CScopeController::OnGrabPeriod(int GrabPeriod)
{
    m_Grabber.SetGrabPeriod(GrabPeriod);
}
