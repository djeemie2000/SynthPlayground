#ifndef MASTERVOLUMEI_H
#define MASTERVOLUMEI_H

class IMasterVolume
{
public:
    ~IMasterVolume(){}

    virtual void SetMasterVolume(float Volume) =0;
};

#endif // MASTERVOLUMEI_H
