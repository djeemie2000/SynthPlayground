#ifndef GLITCHOPERATOR_H
#define GLITCHOPERATOR_H

template<class T>
class CGlitchOperator
{
public:
    CGlitchOperator()
     : m_GrainSize(6)
     , m_GrainOffset(0)
     , m_GrainSpeed(0)
    {}

    void SetGrainSize(int GrainSize)
    {
        m_GrainSize = GrainSize;
    }

    void SetGrainOffset(int GrainOffset)
    {
        m_GrainOffset = GrainOffset;
    }

    void SetGrainSpeed(int Speed)
    {
        m_GrainSpeed = Speed;
    }

    void Process(const T* Source, T* Destination, int NumFrames)
    {
        int GrainSizeMask = 0xFFFFFFFF >> (32-m_GrainSize);
        int Offset = m_GrainOffset;//1 << m_GrainOffset;
        int SpeedShiftLeft = 0<m_GrainSpeed ? m_GrainSpeed : 0;
        int SpeedShiftRight = m_GrainSpeed<0 ? -m_GrainSpeed : 0;
        for(int idx = 0; idx<NumFrames; ++idx)
        {
            int SrcIdx = Offset + ( (idx << SpeedShiftLeft >> SpeedShiftRight) & GrainSizeMask);
            *(Destination+idx) = *(Source + SrcIdx);
        }
    }

private:
    int m_GrainSize;
    int m_GrainOffset;
    int m_GrainSpeed;
};

#endif // GLITCHOPERATOR_H
