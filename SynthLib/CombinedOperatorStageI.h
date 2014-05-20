#ifndef COMBINEDOPERATORSTAGE_H
#define COMBINEDOPERATORSTAGE_H

class ICombinedOperatorStage
{
public:
    virtual ~ICombinedOperatorStage(){}

    virtual void OnSync() =0;
    virtual void OnCombinor(int Selected) =0;
    virtual void OnOperator(int Idx, int Selected) =0;
    virtual void OnAmplitude(int Idx, float Amplitude) =0;
    virtual void OnFrequencyMultiplier(int Idx, float FrequencyMultiplier) =0;
    virtual void OnPhaseshift(int Idx, float PhaseShift) =0;

};

#endif // COMBINEDOPERATORSTAGE_H
