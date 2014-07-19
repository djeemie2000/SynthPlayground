#ifndef SELECTABLEOPERATORFACTORY_H
#define SELECTABLEOPERATORFACTORY_H

#include <vector>
#include <string>
#include "SelectableOperator.h"

class CSelectableOperatorFactory
{
public:
//    CSelectableOperatorFactory();

    static std::vector<std::string> SelectionList()
    {
        return {"RampUp", "RampDown", "Triangle", "FullPseudoSin", "PseudoSin", "Quadratic", "InvQuadratic", "Square", "SquareQuadratic", "RampUpDown", "NoOp" };
    }

    static CSelectableOperator<float> Create();
};

#endif // SELECTABLEOPERATORFACTORY_H
