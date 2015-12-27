#ifndef INTBINARYPATTERN
#define INTBINARYPATTERN

namespace isl
{

template<class T>
int CalcBitCount(T In)
{
    // http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
    int Count = 0;
    for(; In; ++Count)
    {
        In &= In -1;// clear the least significant bit set
    }
    return Count;
}

/*!
 * T must be unsigned!
 */
template<class T>
class CBinaryPattern
{
public:
    CBinaryPattern()
     : m_Pattern(0)
    {}

    void Reset(T Pattern)
    {
        m_Pattern = Pattern;
    }

    void Next()
    {
        ++m_Pattern;
    }

    void Prev()
    {
        --m_Pattern;
    }

    void JumpNext(T Jump)
    {
        m_Pattern += Jump;
    }

    void JumpPrev(T Jump)
    {
        m_Pattern -= Jump;
    }

    void RotateNext()
    {
        m_Pattern = (m_Pattern<<1) | (m_Pattern >> (PatternCapacity-1));
    }

    void RotatePrev()
    {
        m_Pattern = (m_Pattern>>1) | (m_Pattern << (PatternCapacity-1));
    }

    void Invert()
    {
        m_Pattern = ~m_Pattern;
    }

    void Mirror()
    {
        // http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious
        T v = m_Pattern;
        T r = v;

        int s = PatternCapacity - 1; // extra shift needed at end

        for (v >>= 1; v; v >>= 1)
        {
          r <<= 1;
          r |= v & 1;
          s--;
        }
        r <<= s; // shift when v's highest bits are zero

        m_Pattern = r;
    }

    T Get() const
    {
        return m_Pattern;
    }

    bool GetBit(int Bit)
    {
        return m_Pattern & 1<<Bit;
    }

    void NextFixedBitCount(int FixedBitCount)
    {
        // Note: this will cause infinite loop if BitCount is not in [0,sizeof(T)*8]
        int BitCount = PatternCapacity+1;
        while(BitCount!=FixedBitCount)
        {
            ++m_Pattern;
            BitCount = CalcBitCount<T>(m_Pattern);
        }
    }

    void PrevFixedBitCount(int FixedBitCount)
    {
        // Note: this will cause infinite loop if BitCount is not in [0,sizeof(T)*8]
        int BitCount = PatternCapacity+1;
        while(BitCount!=FixedBitCount)
        {
            --m_Pattern;
            BitCount = CalcBitCount<T>(m_Pattern);
        }
    }

    void ResetFixedBitCount(int BitCount)
    {
        m_Pattern = 0;
        Invert();
        m_Pattern = m_Pattern >> (PatternCapacity-BitCount);
    }

private:
    const int PatternCapacity = sizeof(T)*8;

    T m_Pattern;
};

}

#endif // INTBINARYPATTERN
