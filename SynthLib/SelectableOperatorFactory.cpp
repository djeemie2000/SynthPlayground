#include "SelectableOperatorFactory.h"
#include "RampUp.h"
#include "RampDown.h"
#include "Triangle.h"
#include "FullPseudoSin.h"
#include "Square.h"
#include "InvSquare.h"
#include "SquareWave.h"
#include "RampUpDown.h"
#include "SquareQuadratic.h"
#include "NoOp.h"

//CSelectableOperatorFactory::CSelectableOperatorFactory()
//{
//}

//std::vector<std::string> CSelectableOperatorFactory::SelectionList()
//{
//    return {"RampUp", "RampDown", "Triangle", "FullPseudoSin", "PseudoSin", "Quadratic", "InvQuadratic", "Square", "SquareQuadratic", "RampUpDown", "NoOp" };
//}

CSelectableOperator<float> CSelectableOperatorFactory::Create()
{
    CSelectableOperator<float> Op;

    Op.Add(CRampUp<float>());
    Op.Add(CRampDown<float>());
    Op.Add(CTriangle<float>());
    Op.Add(CFullPseudoSin<float>());
    Op.Add(CPseudoSin<float>());
    Op.Add(CQuadratic<float>());
    Op.Add(CInvSquare<float>());
    Op.Add(CSquareWave<float>());
    Op.Add(CSquareQuadratic<float>());
    Op.Add(CRampUpDown<float>());
    Op.Add(CNoOp<float>());

    return Op;
}
