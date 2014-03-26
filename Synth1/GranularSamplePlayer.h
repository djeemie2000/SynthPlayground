#pragma once

//#include <inttypes.h>
#include <vector>
#include <cmath>

template<class T>
class CGranularSamplePlayer
{
public:
    typedef std::vector<T> SampleContainerType;

    CGranularSamplePlayer()
        : m_SampleSize(), m_SampleIndex(0), m_SampleBegin(0), m_Begin(0), m_End(0)
    {}

    void Reset(const SampleContainerType& Sample)
    {
        m_SampleIndex = 0.0f;
        m_SampleSize = Sample.size();
        m_SampleBegin = Sample.data();
        m_Begin = 0.0f;
        m_End = m_SampleSize;
    }

    void SetInterval(int Begin, int End)
    {
        // check wrt sample size and zero
        m_Begin = std::max(0.0f, float(Begin));
        m_End = std::min(float(End), m_SampleSize);
        m_SampleIndex = m_Begin;
    }

    T operator()(float SampleStep)
    {
        //int Index = std::floor(m_SampledIndex);
        m_SampleIndex += SampleStep;
        if(m_End<=m_SampleIndex)
        {
            m_SampleIndex = m_Begin;
        }
//        if(m_SampleSize<m_SampleIndex)
//        {
//            m_SampleIndex -= m_SampleSize;
//        }
        return *(m_SampleBegin + int(m_SampleIndex));
    }

private:
    float m_SampleSize;
    float m_SampleIndex;
    const T* m_SampleBegin;
    float m_Begin;
    float m_End;
};



