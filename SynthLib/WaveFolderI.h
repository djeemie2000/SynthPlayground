#ifndef WAVEFOLDERI_H
#define WAVEFOLDERI_H

class IWaveFolder
{
public:
    virtual ~IWaveFolder() {}

    virtual void OnWaveFold(float Fold) =0;

};

#endif // WAVEFOLDERI_H
