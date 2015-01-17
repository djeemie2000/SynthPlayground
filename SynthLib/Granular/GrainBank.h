#ifndef GRAINBANK_H
#define GRAINBANK_H

#include <vector>
#include "Grain.h"
#include "GrainUtilities.h"

template<class T>
class CGrainBank
{
public:
    CGrainBank(int NumGrains)
        : m_NumGrains(NumGrains)
        , m_Grain(NumGrains)
        , m_CurrentGrainIndex(0)
    {}

    ~CGrainBank()
    {}

    T operator()(const T* Buffer, int BufferSize,
                 bool Trigger,
                 int GrainPosition, int GrainSize, int GrainSpeed, T GrainAmplitude)
    {
        if(Trigger)
        {
            // Note: no check if this grain IsRunning()
            m_Grain[m_CurrentGrainIndex].Start(GrainPosition, GrainSize, GrainSpeed, GrainAmplitude);
            m_CurrentGrainIndex = grainutilities::UpdateCounter(m_CurrentGrainIndex, 1, m_NumGrains);
        }

        // add all grain's output
        T Out = 0;
        for(auto& Grain : m_Grain)
        {
            Out += Grain(Buffer, BufferSize);
        }

        return Out;
    }

private:
    const int m_NumGrains;
    std::vector<CGrain<T>> m_Grain;
    int m_CurrentGrainIndex;
};

#endif // GRAINBANK_H
