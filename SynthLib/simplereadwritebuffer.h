#ifndef SIMPLEREADWRITEBUFFER_H
#define SIMPLEREADWRITEBUFFER_H

#include <vector>
#include <atomic>
#include <cmath>

template<class T>
class CSimpleReadWriteBuffer
{
public:
    CSimpleReadWriteBuffer(int Capacity)
        : m_Capacity(Capacity)
        , m_Buffer(Capacity)
        , m_ReadIndex(0)
        , m_WriteIndex(0)
    {}

    int Write(const T* Data, int Size)
    {
//        if(m_Capacity<Size)
//        {
//            // refuse to write if above capacity
//            return 0;
//        }

        int ReadIndex = m_ReadIndex;
        int WriteCapacity = m_WriteIndex<ReadIndex ? ReadIndex-m_WriteIndex : ReadIndex-m_WriteIndex+m_Capacity;
        int WriteSize = std::min(Size,WriteCapacity);

        if(m_WriteIndex+WriteSize<=m_Capacity)
        {
            std::copy(Data, Data+WriteSize, m_Buffer.data()+m_WriteIndex);
            m_WriteIndex += WriteSize;
        }
        else
        {
            int Part1 = m_Capacity-m_WriteIndex;
            std::copy(Data, Data+Part1, m_Buffer.data()+m_WriteIndex);
            int Part2 = WriteSize-Part1;
            std::copy(Data+Part1, Data+WriteSize, m_Buffer.data());
            m_WriteIndex = Part2;
        }
        return WriteSize;
    }

    int Read(T* Dst, int Size)
    {
        // 'grab' write index, it can only advance while we are executing code below:
        int WriteIndex = m_WriteIndex;
        int ReadCapacity = m_ReadIndex<=WriteIndex ? WriteIndex-m_ReadIndex : WriteIndex-m_ReadIndex+m_Capacity;
        int ReadSize = Size<ReadCapacity ? Size : ReadCapacity;
        if(m_ReadIndex+ReadSize<=m_Capacity)
        {
            std::copy(m_Buffer.data()+m_ReadIndex, m_Buffer.data()+m_ReadIndex+ReadSize, Dst);
            m_ReadIndex += ReadSize;
        }
        else
        {
            int Part1 = m_Capacity-m_ReadIndex;
            std::copy(m_Buffer.data()+m_ReadIndex, m_Buffer.data()+m_ReadIndex+Part1, Dst);
            int Part2 = ReadSize-Part1;
            std::copy(m_Buffer.data(), m_Buffer.data()+Part2, Dst+Part1);
            m_ReadIndex = Part2;
        }
        return ReadSize;
    }

private:
    const int m_Capacity;
    std::vector<T> m_Buffer;
    std::atomic<int> m_ReadIndex;
    std::atomic<int> m_WriteIndex;
};

#endif // SIMPLEREADWRITEBUFFER_H

