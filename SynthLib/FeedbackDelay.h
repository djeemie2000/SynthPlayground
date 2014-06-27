#pragma once

#include "DelayLine.h"

template<class T, class U = T>
class CFeedbackDelay
{
public:
    CFeedbackDelay(int Capacity, T DefaultValue)
        : m_DelayLine(Capacity, DefaultValue)
        , m_PrevIn(DefaultValue)
        , m_PrevDelayLineOutput(DefaultValue)
        , m_Wet(0)
        , m_Feedback(0)
    {}

    void SetDelay(int Delay)
    {
        m_DelayLine.SetDelay(Delay);
    }

    void SetWet(U Wet)
    {
        m_Wet = Wet;
    }

    void SetFeedback(U Feedback)
    {
        m_Feedback = Feedback;
    }

    T operator()(T In)
    {
        // use feedback. Therefore a the previous output value from the delay line is remembered.
        // Feedback parameter determines the mix between the previous delay line output and the current input,
        // which is fed into the delay line
        // output signal is a mix of wet (delay line output) and dry signal (In)
                    //T InputValue = (1-m_Feedback)*In + m_Feedback*m_PrevValue;
        T InputValue = m_PrevIn + m_Feedback*m_PrevDelayLineOutput;
        m_PrevDelayLineOutput = m_DelayLine(InputValue);
        m_PrevIn = In;
        return m_Wet*m_PrevDelayLineOutput + (1-m_Wet)*In;

//        U WetMix = m_Wet;
//        U DryMix = (1-m_Wet);
//        T InInternal = In/2;

//        T DelayLineOut = m_DelayLine();
//        T Out = DryMix*InInternal + WetMix*DelayLineOut;
//        T DelayLineIn = InInternal + m_Feedback*DelayLineOut;
//        m_DelayLine(DelayLineIn);
//        return Out;

        //T PrevIn = m_PrevIn;
//        T DelayLineInput = (1-m_Feedback)*m_PrevIn + m_Feedback*m_PrevDelayLineOutput;
//        m_PrevIn = In;

//        T DelayLineOutput = m_DelayLine(DelayLineInput);
//        m_PrevDelayLineOutput = DelayLineOutput;

//        T OutWet = m_Wet*DelayLineOutput;
//        T OutDry = (1-m_Wet)*In;

//        T OutMix = OutWet + OutDry; //m_Wet*DelayLineOutput + (1-m_Wet)*In;

////        std::cout << In << " "
////                  << PrevIn << " "
////                  << DelayLineInput << " "
////                  << DelayLineOutput << " "
////                  << OutWet << " "
////                  << OutDry << " "
////                  << OutMix << std::endl;

//        return OutMix;

    }

private:
    CDelayLine<T> m_DelayLine;
    T m_PrevIn;
    T m_PrevDelayLineOutput;
    U m_Wet;
    U m_Feedback;
};
