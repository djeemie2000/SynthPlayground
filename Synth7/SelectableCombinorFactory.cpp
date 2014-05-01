#include "SelectableCombinorFactory.h"
#include "Combinor.h"

CSelectableCombinorFactory::CSelectableCombinorFactory()
{
}

std::vector<std::string> CSelectableCombinorFactory::SelectionList()
{
    return {"+L", "*", "M", "m", "|-|", "DivA", "DivB" };
}

CSelectableCombinor<float> CSelectableCombinorFactory::Create()
{
    CSelectableCombinor<float> Combinor;

    Combinor.Add(CHardLimitAdder<float>());
    Combinor.Add(CMultiplier<float>());
    Combinor.Add(CMaxer<float>());
    Combinor.Add(CMiner<float>());
    Combinor.Add(CDiffer<float>());
    Combinor.Add(CDividerA<float>());
    Combinor.Add(CDividerB<float>());

    return Combinor;
}
