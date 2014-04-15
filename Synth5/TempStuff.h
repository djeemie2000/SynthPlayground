#include <iostream>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <fstream>
#include "WriteWavFile.h"

using namespace std;


typedef std::vector<float> FloatList;
typedef std::vector<std::uint8_t> U8List;
typedef std::vector<std::uint16_t> U16List;

float PhaseStep(float Frequency, int SamplingFrequency)
{
    // phase considered [0,1]
    // period_in_samples = SamplingFrequency/Frequency
    // => phase step = 1/period_in_samples
    //
    return Frequency/SamplingFrequency;
}

//FloatList GenerateSawUp(float Frequency, int SamplingFrequency, int Size)
//{
//    FloatList Generated(Size, 0);

//    float DeltaPhase = PhaseStep(Frequency, SamplingFrequency);
//    float Phase = 0.0f;

//    for(auto& Value : Generated)
//    {
//        Value = Phase;
//        Phase = 1.0f<Phase ? Phase-1.0f : Phase+DeltaPhase;
//    }

//    return Generated;
//}

//FloatList GenerateSawDown(float Frequency, int SamplingFrequency, int Size)
//{
//    FloatList Generated(Size, 0);

//    float DeltaPhase = PhaseStep(Frequency, SamplingFrequency);
//    float Phase = 0.0f;

//    for(auto& Value : Generated)
//    {
//        Value = 1.0f-Phase;
//        Phase = 1.0f<Phase ? Phase-1.0f : Phase+DeltaPhase;
//    }

//    return Generated;
//}

//FloatList GeneratePseudoSin(float Frequency, int SamplingFrequency, int Size)
//{
//    FloatList Generated(Size, 0);

//    float DeltaPhase = PhaseStep(Frequency, SamplingFrequency);
//    float Phase = 0.0f;

//    for(auto& Value : Generated)
//    {
//        Value = 1-(1-2*Phase)*(1-2*Phase);
//        Phase = 1.0f<Phase ? Phase-1.0f : Phase+DeltaPhase;
//    }

//    return Generated;
//}

//template<class GeneratorType>
//FloatList GenerateSome(float  Frequency, int SamplingFrequency, int Size, GeneratorType Generator)
//{
//    FloatList Generated(Size, 0);

//    float DeltaPhase = PhaseStep(Frequency, SamplingFrequency);
//    float Phase = 0.0f;

//    for(auto& Value : Generated)
//    {
//        Value = Generator(Phase);
//        Phase += DeltaPhase;
//        Phase = 1.0<Phase ? Phase-1.0 : Phase;
//    }

//    return Generated;
//}

//template<class GeneratorType>
//FloatList GenerateSome2(float  Frequency, int SamplingFrequency, int Size)
//{
//    FloatList Generated(Size, 0);

//    float DeltaPhase = PhaseStep(Frequency, SamplingFrequency);
//    float Phase = 0.0f;

//    GeneratorType Generator;
//    for(auto& Value : Generated)
//    {
//        Value = Generator(Phase);
//        Phase += DeltaPhase;
//        Phase = 1.0f<Phase ? Phase-1.0f : Phase;
//    }

//    return Generated;
//}



U8List ConvertToU8List(const FloatList& Src)
{
    U8List Dst(Src.size(), 0);

    std::transform(Src.begin(), Src.end(), Dst.begin(), [](const float& SrcValue){ return 255*SrcValue; });

    return Dst;
}

U16List ConvertToU16List(const FloatList& Src)
{
    U16List Dst(Src.size(), 0);

    std::transform(Src.begin(), Src.end(), Dst.begin(), [](const float& SrcValue){ return 0xFFFF*SrcValue; });

    return Dst;
}

void ExportU8List(const U8List& Src, std::ostream& Out)
{
    for(auto& Value : Src)
    {
        Out << static_cast<int>(Value) << std::endl;
    }
}

void ExportU8List(U8List::const_iterator Begin, U8List::const_iterator End, std::ostream& Out)
{
    while(Begin<End)
    {
        Out << static_cast<int>(*Begin) << std::endl;
        ++Begin;
    }
}


template<class T>
T MinPhase()
{
    return static_cast<T>(0);
}

template<class T>
T MaxPhase()
{
    return static_cast<T>(1);
}

template<class T>
class PhaseGenerator
{
public:
    PhaseGenerator(const T& SamplingFrequency)
        : m_SamplingFrequency(SamplingFrequency)
        , m_Frequency(1)
        , m_PhaseStep(MinPhase<T>())
        , m_Phase(MinPhase<T>())
    {
        UpdatePhaseStep();
    }

    void SetFrequency(const T& Frequency)
    {
        m_Frequency = Frequency;
        UpdatePhaseStep();
    }

    void SetSamplingFrequency(const T& SamplingFrequency)
    {
        m_SamplingFrequency = SamplingFrequency;
        UpdatePhaseStep();
    }

    T operator()()
    {
        m_Phase += m_PhaseStep;
        if(MaxPhase<T>() < m_Phase)
        {
            m_Phase -= MaxPhase<T>();
        }
        return m_Phase;
    }

    T OnTick()
    {
        m_Phase += m_PhaseStep;
        if(MaxPhase<T>() <= m_Phase)
        {
            m_Phase -= MaxPhase<T>();
        }
        return m_Phase;
    }
private:
    void UpdatePhaseStep()
    {
        m_PhaseStep = m_Frequency/m_SamplingFrequency;
    }

    T m_SamplingFrequency;
    T m_Frequency;
    T m_PhaseStep;
    T m_Phase;
};

template<class T>
class PseudoSin
{
public:
    T operator()(const T& Phase) const
    {
        return 1-(1-2*Phase)*(1-2*Phase);
        // = 1-( 1 - 2*Phase -2*Phase + 4*Phase*Phase )
        // = 1-( 1 -4*Phase + 4*Pahse*Phase)
        // = -4*Phase + 4*Phase*Phase
        // = 4*Phase*(Phase-1)
    }
};

template<class T>
class PseudoSin2
{
public:
    T operator()(const T& Phase) const
    {
        //return 1-(1-2*Phase)*(1-2*Phase);
        // = 1-( 1 - 2*Phase -2*Phase + 4*Phase*Phase )
        // = 1-( 1 -4*Phase + 4*Pahse*Phase)
        // = 4*Phase - 4*Phase*Phase
        //
        return 4*Phase*(1-Phase);
    }
};

template<class T>
class PseudoSinRampUp
{
public:
    T operator()(const T& Phase) const
    {
        return Phase*(2-Phase);
    }
};

template<class T>
class NoOp
{
public:
    T operator()(const T& Phase) const
    {
        return Phase;
    }
};

template<class T>
class FullPseudoSin
{
public:
    T operator()(const T& Phase)
    {
        // Phase<0.5 => 0.5 + 0.5 * PseudoSin(2*Phase)      = 0.5 * ( 1 + PseudoSin(2*Phase) )
        // Phase>0.5 => 0.5 - 0.5 * PseudoSin(2*(Phase-0.5)) = 0.5 * (1 - PseudoSin(2*Phase-1) )
        return Phase<0.5f  ? 0.5f * (1 + PseudoSin2<T>()(2*Phase)) : 0.5f * (1 - PseudoSin<T>()(2*Phase-1));//TODO
    }
};

template<class T>
class Linear
{
public:
    Linear()
        : m_Min(0)
        , m_Max(1)
    {
        Calc();
    }

    T operator()(const T& Phase)
    {
        return m_Offset + m_Slope*Phase;
        // return m_Min + (m_Max-m_Min)*Phase;
        // return m_Min*(1-Phase) + m_Max*Phase
    }

    void SetMin(const T& Min)
    {
        m_Min = Min;
        Calc();
    }

    void SetMax(const T& Max)
    {
        m_Max = Max;
        Calc();
    }

    void SetSymmetrical(const T& Offset)
    {
        m_Min = Offset;
        m_Max = 1 - Offset;
        Calc();
    }

private:
    void Calc()
    {
        m_Offset = m_Min;
        m_Slope = m_Max - m_Min;
    }

    T m_Min;
    T m_Max;
    T m_Offset;
    T m_Slope;
};

template<class T>
class Square
{
public:
    T operator()(const T& Phase) const
    {
        return Phase*Phase;
    }
};

template<class T, class GeneratorType, class FilterType>
class Combiner
{
public:
    Combiner(const GeneratorType& Generator, FilterType& Filter)
        : m_Generator(Generator)
        , m_Filter(Filter)
    {}

    T operator()()
    {
        return m_Filter(m_Generator());
    }

    GeneratorType m_Generator;
    FilterType  m_Filter;
private:

};



void Test1()
{
    const float SamplingFrequency = 44100;

    float BaseFrequency = 88.0f;
    PhaseGenerator<float> PhaseGen1(SamplingFrequency);
    PhaseGen1.SetFrequency(1.000f*BaseFrequency);
    PhaseGenerator<float> PhaseGen2(SamplingFrequency);
    PhaseGen2.SetFrequency(1.01f*BaseFrequency);
    PhaseGenerator<float> PhaseGen3(SamplingFrequency);
    PhaseGen3.SetFrequency(0.495f*BaseFrequency);
    PhaseGenerator<float> PhaseGen4(SamplingFrequency);
    PhaseGen4.SetFrequency(0.505f*BaseFrequency);

    FullPseudoSin<float> Gen;
    PseudoSin<float> Gen2;
    PseudoSinRampUp<float> Gen3;
    Linear<float> Lin1;
    Lin1.SetSymmetrical(0.01);

//    typedef Combiner<float, PhaseGenerator<float>, PseudoSin2<float>> Combi1Type;
//    Combi1Type Combi1(PhaseGen1, PseudoSin2<float>());

    Square<float> Sq;
//    typedef Combiner<float, Square<float>, Combi1Type> Combi2Type;
//    Combi2Type Combi2(Sq, Combi1);

    int Size = static_cast<int>(SamplingFrequency*10);
    FloatList Generated(Size, 0.0f);
    for(auto& Value : Generated)
    {
//        Value = Gen2(Gen( 0.25f * (    Gen(Gen(Sq(PhaseGen1())))
//                                    +  Gen(Gen(Sq(PhaseGen2())))
//                                    +  Gen(Gen(Sq(PhaseGen3())))
//                                    +  Gen(Gen(Sq(PhaseGen4())))   ) ));
        //Value = Gen3( 0.25 * ( Gen3(PhaseGen1()) + Gen2(PhaseGen2()) + Gen(PhaseGen3()) + Gen2(PhaseGen4()) ) );
        //Value = NoOp<float>()(( Gen(PhaseGen1()) + Gen(PhaseGen3()) + Gen(PhaseGen2()) + Gen(PhaseGen4()) ) * 0.25 );
        Value = ( Gen(Lin1(PhaseGen1())) + Gen(Lin1(PhaseGen4())) + Gen(Lin1(PhaseGen3())) ) * 0.33;
    }

    U8List GeneratedU8 = ConvertToU8List(Generated);
    U16List GeneratedU16 = ConvertToU16List(Generated);

    const std::string Path = "Exported21.txt";
    std::ofstream OutFile(Path.c_str());
    if(OutFile.is_open())
    {
        ExportU8List(GeneratedU8.begin(), GeneratedU8.begin()+2500, OutFile);
    }

    writeWAVData<std::uint8_t>("Exported19w.wav", GeneratedU8.data(), GeneratedU8.size(), SamplingFrequency, 1);

}

int main()
{
    cout << "Hello World!" << endl;

    Test1();

    cout << "Done!" << std::endl;
//    const std::string Path = "Exported4.txt";
//    std::ofstream OutFile(Path.c_str());
//    if(OutFile.is_open())
//    {
//        //ExportU8List(ConvertToU8List(GeneratePseudoSin(400, 44100, 500)), OutFile);
//        //ExportU8List(ConvertToU8List(GenerateSome(400, 44100, 500, [](const float& Phase){return 1-(1-2*Phase)*(1-2*Phase);})), OutFile);
//        ExportU8List(ConvertToU8List(GenerateSome2<PseudoSin2<float>>(400, 44100, 500)), OutFile);

//    }

    return 0;
}

