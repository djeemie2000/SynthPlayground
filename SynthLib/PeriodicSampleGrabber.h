#ifndef PERIODICSAMPLEGRABBER_H
#define PERIODICSAMPLEGRABBER_H

#include <cmath>
#include <algorithm>

template<class T>
class CPeriodicSampleGrabber
{
public:
    CPeriodicSampleGrabber()
     : m_GrabPeriod(512)
     , m_PeriodCounter(512)
     , m_GrabSize(512)
     , m_GrabbedSample(512)
     //, m_WriteIndex(0)
    {}

    void SetGrabSize(int GrabSize)
    {
        m_GrabSize = GrabSize;
        m_GrabbedSample.resize(m_GrabSize);
//        if(m_GrabSize<=m_WriteIndex)
//        {
//            m_WriteIndex = 0;//??
//        }
    }

    void SetGrabPeriod(int GrabPeriod)
    {
        //if(m_GrabSize<=GrabPeriod)
        //{
            m_GrabPeriod = GrabPeriod;
            m_PeriodCounter = 0;
        //}
    }

    bool OnRead(const T* Sample, int SampleSize)
    {
        bool Read = false;
        if(Sample)
        {
            // naive implementation
            for(int SampleIdx = 0; SampleIdx<SampleSize; ++SampleIdx)
            {
                if(m_PeriodCounter<m_GrabSize)
                {
                    m_GrabbedSample[m_PeriodCounter] = Sample[SampleIdx];
                    Read = true;
                }

                ++m_PeriodCounter;
                if(m_GrabPeriod<=m_PeriodCounter)
                {
                    m_PeriodCounter = 0;
                }
            }
        }
        return Read;
        // must grab if period cntr is in [0, GrabSize]
//        if(m_GrabPeriod<=m_PeriodCounter+SampleSize)
//        {
//            // must grab
//            // read sample from
//            int ReadIndex = (m_PeriodCounter+SampleSize)%m_GrabPeriod;
//            int ReadIndexEnd = std::min(ReadIndex+SampleSize, m_GrabSize);

//            // write sample into [m_WriteIndex, m_WriteIndex+SampleSize[
//            // or [m_WriteIndex, m_GrabSize[ if m_WriteIndex+SampleSize exceeds m_GrabSize
//            int WriteIndex = m_WriteIndex;
//            //int WriteIndexEnd = std::min(m_WriteIndex+SampleSize, m_GrabSize);
//            int GrabSize = ReadIndexEnd-ReadIndex;
//            std::copy(Sample+ReadIndex, Sample+ReadIndexEnd, m_GrabbedSample.begin()+WriteIndex);

//            m_WriteIndex += GrabSize;
//            if(m_GrabSize<=m_WriteIndex)
//            {
//                m_WriteIndex = 0;
//            }
//        }
//        m_PeriodCounter += SampleSize;
    }

    const std::vector<T>& GetGrabbedSample() const
    {
        return m_GrabbedSample;
    }

private:
    int m_GrabPeriod;
    int m_PeriodCounter;
    int m_GrabSize;
    std::vector<T> m_GrabbedSample;
//    int m_WriteIndex;
};

#endif // PERIODICSAMPLEGRABBER_H
