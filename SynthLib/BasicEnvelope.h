#ifndef BASICENVELOPE_H
#define BASICENVELOPE_H

template<class T>
class CBasicEnvelope
{
public:
    CBasicEnvelope()
        : m_Amplitude(0)
    {}

    void NoteOn()
    {
        m_Amplitude = 1;
    }

    void NoteOff()
    {
        m_Amplitude = 0;
    }

    T operator()()
    {
        return m_Amplitude;
    }

private:
    T m_Amplitude;
};


#endif // BASICENVELOPE_H
