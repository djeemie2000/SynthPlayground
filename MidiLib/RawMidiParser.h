#ifndef RAWMIDIPARSER_H
#define RAWMIDIPARSER_H

#include <vector>
#include <cstdint>

class IMidiHandler;

class CRawMidiParser
{
public:
    CRawMidiParser(IMidiHandler& MidiHandler);

    void Parse(const std::vector<std::uint8_t>& RawMidiData);
    void Parse(const std::vector<std::uint8_t>& RawMidiData, IMidiHandler& MidiHandler);


private:
    IMidiHandler& m_MidiHandler;
    std::vector<std::uint8_t> m_RawMidiDataBuffer;
};

#endif // RAWMIDIPARSER_H
