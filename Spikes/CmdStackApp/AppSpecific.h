#ifndef APPSPECIFIC_H
#define APPSPECIFIC_H

#include "CommandStack.h"

class CAppSpecificController
{
public:
    CAppSpecificController();

    void BoolCommand1(bool Value);
    void BoolCommand2(bool Value);
    void IntCommand1(int Value);
    void IntCommand2(int Value);
    void FloatCommand1(float Value);
    void FloatCommand2(float Value);
    void Command1();
};

CmdFunctionMap BuildAppSpecificCmdFunctionMap(CAppSpecificController& Controller);
CmdStack BuildAppSpecificDefaults();


#endif // APPSPECIFIC_H
