#ifndef INTERPOLATINGOPERATORI_H
#define INTERPOLATINGOPERATORI_H

class IInterpolatingOperator
{
public:
    virtual ~IInterpolatingOperator(){}

    virtual void SelectOperator1(int Selected) =0;
    virtual void SelectOperator2(int Selected) =0;
    virtual void SetMix(float Mix) =0;
    virtual void SetMixModAmt(float ModAmt) =0;
};

#endif // INTERPOLATINGOPERATORI_H
