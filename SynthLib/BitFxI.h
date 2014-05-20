#ifndef BITFXI_H
#define BITFXI_H

class IBitFx
{
public:
    virtual ~IBitFx(){}

    virtual void OnBitCrusherDepth(int Depth) =0;
    virtual void OnSampleAndHoldPeriod(int Period) =0;
    virtual void OnRipplerStrength(int Strength) =0;
};

#endif // BITFXI_H
