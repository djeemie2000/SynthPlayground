#pragma once

template<class T, int Min = -1, int Max = 1>
class CPhaseShifter
{
public:
    static constexpr T MinPhase = static_cast<T>(Min);
    static constexpr T MaxPhase = static_cast<T>(Max);
    static constexpr T PhaseRange = MaxPhase - MinPhase;

    CPhaseShifter()
    {
    }

    T operator()(T Phase, T PhaseShift)
    {
        // assumes both Phase and PhaseShift are in [MinPhase, MaxPhase]
        T Out = Phase + PhaseShift;
        if(MaxPhase<Out)
        {
            Out -= PhaseRange;
        }
        else if(Out<MinPhase)
        {
            Out += PhaseRange;
        }
        return Out;
    }

};
