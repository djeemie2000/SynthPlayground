#ifndef FEEDBACKDELAYI_H
#define FEEDBACKDELAYI_H

class IFeedbackDelay
{
public:
    virtual ~IFeedbackDelay(){}

    virtual void OnDelayMilliSeconds(float Delay) =0;
    virtual void OnDelayFeedback(float Feedback) = 0;
    virtual void OnDelayWetDry(float WetDry) =0; //!< 0 is dry, 1 is wet
    virtual void OnDelayBypass(bool Bypass) =0;
};

#endif // FEEDBACKDELAYI_H
