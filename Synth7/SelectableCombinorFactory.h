#ifndef SELECTABLECOMBINORFACTORY_H
#define SELECTABLECOMBINORFACTORY_H

#include <vector>
#include <string>
#include "SelectableCombinor.h"

class CSelectableCombinorFactory
{
public:
    CSelectableCombinorFactory();

    static std::vector<std::string> SelectionList();

    static CSelectableCombinor<float> Create();
};

#endif // SELECTABLECOMBINORFACTORY_H
