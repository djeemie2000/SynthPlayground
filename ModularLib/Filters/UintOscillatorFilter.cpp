#include "UintOscillatorFilter.h"
#include "IntConversions.h"
#include "IntUtilities.h"

CUintOscillatorFilter::CUintOscillatorFilter(int SamplingFrequency)
    : m_SamplingFrequency(SamplingFrequency)
    , m_Phasor()
    , m_Buffers({100.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f, 0.0f})
{
}

std::vector<std::string> CUintOscillatorFilter::GetInputNames() const
{
    return {"Freq", "Skew", "BitMask"};
}

std::vector<std::string> CUintOscillatorFilter::GetOutputNames() const
{
    return {"SawUp", "SawDown", "Triangle", "Pulse+", "Pulse-"};
}

std::vector<std::string> CUintOscillatorFilter::GetMidiInputNames() const
{
    return {};
}

std::vector<std::string> CUintOscillatorFilter::GetMidiOutputNames() const
{
    return {};
}

int CUintOscillatorFilter::OnProcess(const std::vector<void *> &SourceBuffers,
                                       const std::vector<void *> &DestinationBuffers,
                                       const std::vector<std::shared_ptr<IMidiRenderer>> /*MidiRenderers*/,
                                       const std::vector<std::shared_ptr<IMidiHandler> > /*MidiHandlers*/,
                                       int NumFrames,
                                       std::uint32_t /*TimeStamp*/)
{
    m_Buffers.Update(SourceBuffers, DestinationBuffers, NumFrames);

    const float* FreqBuffer = m_Buffers.GetSourceBuffer(0);
    const float* SkewBuffer = m_Buffers.GetSourceBuffer(1);
    //const float* BitMaskBuffer = m_Buffers.GetSourceBuffer(2);
    float* SawUpBuffer = m_Buffers.GetDestinationBuffer(0);
    float* SawDownBuffer = m_Buffers.GetDestinationBuffer(1);
    float* TriangleBuffer = m_Buffers.GetDestinationBuffer(2);
    float* PulsePosBuffer = m_Buffers.GetDestinationBuffer(3);
    float* PulseNegBuffer = m_Buffers.GetDestinationBuffer(4);

    const float* OutBufferEnd = SawUpBuffer + NumFrames;
    while(SawUpBuffer<OutBufferEnd)
    {
        uisl::uint32_t PhaseIncrease = *FreqBuffer * (1<<InternalScale) /m_SamplingFrequency;

        int Skew = (1+*SkewBuffer)*512;
        if(Skew<1)
        {
            Skew = 1;
        }
        if(1023<Skew)
        {
            Skew = 1023;
        }

        m_Phasor.SetPhaseIncrease(PhaseIncrease, Skew);

        uisl::uint32_t Phase = m_Phasor();

        *SawUpBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale+1>( isl::IntUnipolarToBipolar<Scale+1>( uisl::CalcSawUp<uisl::uint32_t, Scale>(Phase) ) );
        *SawDownBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale+1>( isl::IntUnipolarToBipolar<Scale+1>( uisl::CalcSawDown<uisl::uint32_t, Scale>(Phase) ) );
        *TriangleBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale+1>( isl::IntUnipolarToBipolar<Scale+1>( uisl::CalcTriangle<uisl::uint32_t, Scale>(Phase) ) );
        *PulsePosBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale+1>( isl::IntUnipolarToBipolar<Scale+1>( uisl::CalcPosPulse<uisl::uint32_t, Scale>(Phase) ) );
        *PulseNegBuffer = isl::IntBipolarToFloatBipolar<int, float, Scale+1>( isl::IntUnipolarToBipolar<Scale+1>( uisl::CalcNegPulse<uisl::uint32_t, Scale>(Phase) ) );

        ++FreqBuffer;
        ++SkewBuffer;
        ++SawUpBuffer;
        ++SawDownBuffer;
        ++TriangleBuffer;
        ++PulsePosBuffer;
        ++PulseNegBuffer;
    }

    return 0;
}
