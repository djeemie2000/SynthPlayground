#ifndef BINARYOSCILLATOR
#define BINARYOSCILLATOR

#include <cstdint>
#include "Conversions.h"

template<class T>
class CBinaryOscillator
{
public:
    static constexpr std::uint8_t NumBits = 8;
    static constexpr T MinValue = static_cast<T>(-1);
    static constexpr T MaxValue = static_cast<T>(1);

    CBinaryOscillator()
     //: m_BinaryValue(0x0F)
    {}

//    void SetBinaryValue(int Value)
//    {
//        // 0x00 and 0xFF are illegal, we need some change in the bits
//        if(0<Value && Value<255)
//        {
//            m_BinaryValue = Value;
//        }
//    }

//    T operator()(T Phase)
//    {
//        std::uint8_t Bit = NumBits*BipolarToUnipolar(Phase);// should be a number between 0 and NumBits-1
//        std::uint8_t BitValue = (m_BinaryValue>>Bit & 1);// bit at Bit is 1 or 0
//        return BitValue ? MaxValue : MinValue;
//    }

    T operator()(T Phase, T BinaryVal)
    {
        // Phase        should be in [-1, 1] (bipolar)
        // BinaryVal  should be in [ 0, 1] (unipolar)
        std::uint8_t BinaryValue = 256*BinaryVal;
        BinaryValue = BinaryValue ? BinaryValue : 1;//at least 1
        BinaryValue = BinaryValue==255 ? 254 : BinaryValue; // not 255

        std::uint8_t Bit = NumBits*BipolarToUnipolar(Phase);// should be a number between 0 and NumBits-1
        std::uint8_t BitValue = (BinaryValue>>Bit & 1);// bit at Bit is 1 or 0
        return BitValue ? MaxValue : MinValue;
    }

//private:
//    std::uint8_t m_BinaryValue;
};

#endif // BINARYOSCILLATOR
