#ifndef LPFILTERI_H
#define LPFILTERI_H

class ILPFilter
{
public:
    virtual ~ILPFilter(){}

    virtual void OnLPFilterCutoff(float Parameter) =0;
    virtual void OnLPFilterPoles(int Stages) =0;
    virtual void OnLPFilterFeedback(float Feedback) =0;
};

#endif // LPFILTERI_H
