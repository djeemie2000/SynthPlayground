#ifndef ARENVELOPEI_H
#define ARENVELOPEI_H

class IAREnvelope
{
public:
    virtual ~IAREnvelope(){}

    virtual void OnEnvelopeAttack(float AttackMilliSeconds) =0;
    virtual void OnEnvelopeRelease(float ReleaseMilliSeconds) =0;

};

#endif // ARENVELOPEI_H
