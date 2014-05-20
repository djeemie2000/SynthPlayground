#ifndef NONLINEARSHAPERI_H
#define NONLINEARSHAPERI_H

class INonLinearShaper
{
public:
    virtual ~INonLinearShaper(){}

    virtual void OnNonLinearShaperA(float A) =0;
    virtual void OnNonLinearShaperB(float B) =0;
    virtual void OnNonLinearShaperPreGain(float PreGain) =0;
};

#endif // NONLINEARSHAPERI_H
