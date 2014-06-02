#ifndef LFOI_H
#define LFOI_H

class ILFOs
{
public:
    virtual ~ILFOs(){}

    virtual void SetFrequency(int Idx, float Frequency) =0;
    virtual void SelectWaveform(int Idx, int Selected) =0;
};

#endif // LFOI_H
