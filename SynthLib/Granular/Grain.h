#ifndef GRAIN_H
#define GRAIN_H

#include "GrainWindow.h"

template<class T>
class CGrain
{
public:
    CGrain()
        : m_Cntr(1<<8)
        , m_Position(0)
        , m_Size(m_Cntr)
        , m_Speed(1)
        , m_Amplitude(1)
    {}

    void Start(int Position, int Size, int Speed, T Amplitude)
    {
        m_Cntr = 0;
        m_Position = Position;
        m_Size = Size;
        m_Speed = Speed;
        m_Amplitude = Amplitude;
    }

    bool IsRunning() const
    {
        return m_Cntr<m_Size;
    }

    T operator()(const T* Buffer, int BufferSize)
    {
        if(m_Cntr<m_Size)
        {
            // TODO handle cases where speed is negative
            int Index = m_Position + m_Cntr;
            m_Cntr += m_Speed;
            if(0<=Index && Index<BufferSize)
            {
                // using window!
                return m_Amplitude*m_Window(m_Cntr, m_Size)*Buffer[Index];
                // return m_Amplitude*Buffer[Index];
            }
        }

        return 0;
    }

private:
    int m_Cntr;
    int m_Position;
    int m_Size;
    int m_Speed;
    T m_Amplitude;

    CTriangularGrainWindow<T> m_Window;
};

#endif // GRAIN_H
