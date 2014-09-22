#ifndef MIDIRENDERERI_H
#define MIDIRENDERERI_H

class IMidiHandler;

class IMidiRenderer
{
public:
    virtual ~IMidiRenderer(){}

    virtual void Accept(IMidiHandler& Handler) =0;
};

#endif // MIDIRENDERERI_H
