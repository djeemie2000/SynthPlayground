#ifndef AUDIOFILTERI_H
#define AUDIOFILTERI_H

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

class IMidiRenderer;
class IMidiHandler;

class IAudioFilter
{
public:
    virtual ~IAudioFilter(){}

    virtual std::vector<std::string> GetInputNames() const =0;
    virtual std::vector<std::string> GetOutputNames() const =0;
    virtual std::vector<std::string> GetMidiInputNames() const =0;
    virtual std::vector<std::string> GetMidiOutputNames() const =0;

    /*!
     * \brief OnProcess
     * \param SourceBuffers the source buffers to read from
     * \param DestinationBuffers the destination buffers to write to
     * \param MidiRenderers that render the midi input
     * \param MidiHandlers that handle the midi output
     * \param NumFrames the number of frames to process
     * \param TimeStamp the timestamp (in frames)
     * \return
     */
    virtual int OnProcess(const std::vector<void*>& SourceBuffers,
                          const std::vector<void*>& DestinationBuffers,
                          const std::vector<std::shared_ptr<IMidiRenderer>> MidiRenderers,
                          const std::vector<std::shared_ptr<IMidiHandler>> MidiHandlers,
                          int NumFrames,
                          std::uint32_t TimeStamp) =0;
};

#endif // AUDIOFILTERI_H
