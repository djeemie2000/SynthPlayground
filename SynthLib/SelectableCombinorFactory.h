#ifndef SELECTABLECOMBINORFACTORY_H
#define SELECTABLECOMBINORFACTORY_H

#include <vector>
#include <string>
#include "SelectableCombinor.h"

class CSelectableCombinorFactory
{
public:
    CSelectableCombinorFactory();

    static std::vector<std::string> SelectionList()
    {
        return {"+L", "*1", "*2", "*", "-L", "-||", "M||", "m||", "M", "m", "P+N", "N+P", "DivA", "DivB", "DivC" };
    }

    static CSelectableCombinor<float> Create();
};

//std::vector<std::string> CSelectableCombinorFactory::SelectionList()
//{
//    return {"+L", "*1", "*2", "*", "-L", "-||", "M||", "m||", "M", "m", "P+N", "N+P", "DivA", "DivB", "DivC" };
//}

#endif // SELECTABLECOMBINORFACTORY_H
