#ifndef LFOBANKI_H
#define LFOBANKI_H

class ILFOBank
{
public:
    virtual ~ILFOBank(){}

    virtual void SetLFOFrequency(int Idx, float Frequency) =0;
    virtual void SelectLFOWaveform(int Idx, int Selected) =0;
    virtual int LFOBankSize() const =0;
};

#endif // LFOBANKI_H
