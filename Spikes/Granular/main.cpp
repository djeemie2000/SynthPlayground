#include <iostream>
#include <vector>

using namespace std;

template<class T>
class CGrainWindow
{
public:
    CGrainWindow(){}

    T operator()(int Index, int GrainSize)
    {
        // an integer implementation of Triangle which can be rescaled to T in [0,1]
        return static_cast<T>( 2*Index<GrainSize ? 2*Index : 2*(GrainSize-Index))/static_cast<T>(GrainSize);
        // TODO return m_Op(Phase)
        // Phase should be in [0,1]
        // window should be in [0,1]
        // -> e.g. PseudoSin, Triangle,
        T Phase = static_cast<T>(Index)/static_cast<T>(GrainSize);
        return 4*Phase*(1-Phase);
    }
};

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

    CGrainWindow<T> m_Window;
};

int UpdateCounter(int Counter, int Step, int MaxCounter)
{
    return (Counter+Step)%MaxCounter;
}

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
            m_CurrentGrainIndex = UpdateCounter(m_CurrentGrainIndex, 1, m_NumGrains);
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

class CDensityGrainTrigger
{
public:
    CDensityGrainTrigger()
     : m_Cntr(1<<30)//trigger at initial call, provided density is smaller
    {}

    void Sync()
    {
        m_Cntr = 1<<30;
    }

    bool operator()(int Density)
    {
        if(m_Cntr<Density)
        {
            ++m_Cntr;
            return false;
        }

        m_Cntr = 1;
        return true;
    }

private:
    int m_Cntr;
};


template<class T>
class CBufferGrabber // bad name
{
public:
    typedef std::vector<T> BufferType;

    CBufferGrabber(int Capacity)
     : m_Capacity(Capacity)
     , m_Buffer(Capacity, 0)
     , m_Size(Capacity)
     , m_Grab(false)
     , m_Cntr(0)
    {}

    void SetSize(int Size)
    {
        if(0<= Size && Size<=m_Capacity)
        {
            m_Size = Size;
        }
    }

    void Grab()
    {
        m_Grab = true;
        m_Cntr = 0;
    }

    void operator()(T In)
    {
        if(m_Grab)
        {
            m_Buffer[m_Cntr] = In;

            ++m_Cntr;
            if(m_Size<=m_Cntr)
            {
                m_Grab = false;
            }
        }
    }

    int GetSize() const
    {
        return m_Size;
    }

    const BufferType& GetBuffer() const
    {
        return m_Buffer;
    }

private:
    const int m_Capacity;
    BufferType m_Buffer;
    int m_Size;
    bool m_Grab;
    int m_Cntr;
};



// ----------------------

void TestGrain()
{
    const int BufferSize = 1<<10;
    std::vector<float> Buffer(BufferSize, 0);
    // fill buffer
    float Value = 0.0f;
    for(auto& Val : Buffer)
    {
        Val = Value;
        Value += 1.0f;
    }

    CGrain<float> Grain;

    for(int Repeat = 0; Repeat<10; ++Repeat)
    {
        std::cout << Grain(Buffer.data(), Buffer.size()) << " ";
    }

    Grain.Start(32, 8, 1, 1.0f);

    for(int Repeat = 0; Repeat<16; ++Repeat)
    {
        std::cout << Grain(Buffer.data(), Buffer.size()) << " ";
    }
}

void TestGrainBank()
{
    const int BufferSize = 1<<10;
    std::vector<float> Buffer(BufferSize, 0);
    // fill buffer
    float Value = 0.0f;
    for(auto& Val : Buffer)
    {
        Val = Value;
        Value += 1.0f;
    }

    CDensityGrainTrigger Trigger;
    CGrainBank<float> GrainBank(4);

    for(int Repeat = 0; Repeat<64; ++Repeat)
    {
        int GrainSize = 1<<3;
        int GrainDensity = GrainSize;
        std::cout << GrainBank(Buffer.data(), Buffer.size(),
                               Trigger(GrainDensity),
                               Repeat,
                               GrainSize, 1, 1.0f) << " ";
    }
    cout << endl;

    for(int Repeat = 0; Repeat<32; ++Repeat)
    {
        int GrainSize = 1<<3;
        std::cout << GrainBank(Buffer.data(), Buffer.size(),
                               false,
                               Repeat,
                               GrainSize, 1, 1.0f) << " ";
    }
    cout << endl;

    Trigger.Sync();

    for(int Repeat = 0; Repeat<64; ++Repeat)
    {
        int GrainSize = 1<<3;
        int GrainDensity = GrainSize/2;
        std::cout << GrainBank(Buffer.data(), Buffer.size(),
                               //(Repeat%GrainDensity)==0,
                               Trigger(GrainDensity),
                               Repeat,
                               8, 1, 1.0f) << " ";
    }
    cout << endl;
}

template<class T>
void PrintGrabber(const CBufferGrabber<T>& Grabber)
{
    for(int idx=0; idx<Grabber.GetSize(); ++idx)
    {
        std::cout << Grabber.GetBuffer()[idx] << " ";
    }
    std::cout << std::endl;
}

void TestGrabber()
{
    const int BufferSize = 1<<10;
    std::vector<float> Buffer(BufferSize, 0);
    // fill buffer
    float Value = 0.0f;
    for(auto& Val : Buffer)
    {
        Val = Value;
        Value += 1.0f;
    }

    CBufferGrabber<float> Grabber(1<<8);
    Grabber.SetSize(1<<4);

    PrintGrabber(Grabber);

    for(int Repeat =0; Repeat<32; ++Repeat)
    {
        Grabber(Buffer[Repeat]);
    }

    Grabber.Grab();
    for(int Repeat = 32; Repeat<64; ++Repeat)
    {
        Grabber(Buffer[Repeat]);
    }

    PrintGrabber(Grabber);
}

int main()
{
    cout << "Hello World!" << endl;

    cout << "Hello World!" << endl;
    TestGrain();

    cout << "Hello World!" << endl;
    TestGrainBank();

    cout << "Hello World!" << endl;
    TestGrabber();

    return 0;
}
