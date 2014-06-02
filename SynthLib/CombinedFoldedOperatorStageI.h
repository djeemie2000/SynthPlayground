#ifndef COMBINEDFOLDEDOPERATORSTAGE_H
#define COMBINEDFOLDEDOPERATORSTAGE_H

class ICombinedFoldedOperatorStage
{
public:
    virtual ~ICombinedFoldedOperatorStage(){}

    virtual void OnSync() =0;
    virtual void OnCombinor(int Selected) =0;
    virtual void OnOperator(int Idx, int Selected) =0;
    virtual void OnAmplitude(int Idx, float Amplitude) =0;
    virtual void OnFrequencyMultiplier(int Idx, float FrequencyMultiplier) =0;
    virtual void OnPhaseshift(int Idx, float PhaseShift) =0;
    virtual void OnFold(int Idx, float Fold) =0;
    virtual void OnFoldModAmount(int Oscillator, float Amount) =0;

};

#endif // COMBINEDFOLDEDOPERATORSTAGE_H
