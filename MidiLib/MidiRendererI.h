#ifndef MIDIRENDERERI_H
#define MIDIRENDERERI_H

class IMidiInputHandler;

class IMidiRenderer
{
public:
    virtual ~IMidiRenderer(){}

    virtual void Accept(IMidiInputHandler& Handler) =0;
};

#endif // MIDIRENDERERI_H
