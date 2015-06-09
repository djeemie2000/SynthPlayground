#ifndef BUFFERHANDLERI_H
#define BUFFERHANDLERI_H

template<class T>
class IBufferHandler
{
public:
    virtual ~IBufferHandler(){}

    virtual bool HandleBuffer(const T* Buffer, int Size) =0;
};

#endif // BUFFERHANDLERI_H
