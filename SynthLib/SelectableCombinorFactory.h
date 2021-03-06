#ifndef SELECTABLECOMBINORFACTORY_H
#define SELECTABLECOMBINORFACTORY_H

#include <vector>
#include <string>
#include "SelectableCombinor.h"
#include "Combinor.h"

class CSelectableCombinorFactory
{
public:
    static std::vector<std::string> SelectionList()
    {
        return {"+L", "*1", "*2", "*", "-L", "-||", "M||", "m||", "M", "m", "P+N", "N+P", "R1", "R2", "1+1*2", "2+2*1", "DivA", "DivB", "DivC", "*U" };
    }

    static CSelectableCombinor<float> Create()
    {
        CSelectableCombinor<float> Combinor;

        Combinor.Add(CHardLimitAdd<float>());

        Combinor.Add(CMultFirst<float>());
        Combinor.Add(CMultSecond<float>());
        Combinor.Add(CMult<float>());

        Combinor.Add(CHardLimitDiff<float>());
        Combinor.Add(CDiffAbs<float>());

        Combinor.Add(CMaxAbs<float>());
        Combinor.Add(CMinAbs<float>());
        Combinor.Add(CMax<float>());
        Combinor.Add(CMin<float>());

        Combinor.Add(CPosNegAdd<float>());
        Combinor.Add(CNegPosAdd<float>());

        Combinor.Add(CRingModFirst<float>());
        Combinor.Add(CRingModSecond<float>());

        Combinor.Add(CMultMod1<float>());
        Combinor.Add(CMultMod2<float>());

        Combinor.Add(CDividerA<float>());
        Combinor.Add(CDividerB<float>());
        Combinor.Add(CDividerC<float>());

        Combinor.Add(CMultUnipolar<float>());

        Combinor.Select(0);

        return Combinor;
    }
};

#endif // SELECTABLECOMBINORFACTORY_H
