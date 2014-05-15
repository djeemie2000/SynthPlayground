#include "GuiItems.h"
#include "GuiUtilities.h"
#include <QGroupBox>

#include "Controller.h"


namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "WaveFolder");
    // -> add "Fold" doublespinbox
    AddDoubleSpinBox(Box, Parent, {"Fold", 0.97, 0, 1, 0.01, 2}, [&Controller](double Value){ Controller.OnWaveFold(Value); });
}

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "LPFilter");
    // add "Cutoff" double spin box
    AddDoubleSpinBox(Box, Parent, {"CutOff", 1.0, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnLPFilterParameter(Value); });
    // add "Poles" int spin box
    AddSpinBox(Box, Parent, {"Poles", 1, 1, 24, 1}, [&Controller](int Value){ Controller.OnLPFilterStages(Value); });
    // add "Q" double spin box
    AddDoubleSpinBox(Box, Parent, {"Q", 0.0, -1.0, 2.0, 0.01, 3}, [&Controller](double Value){ Controller.OnLPFilterFeedback(Value); });
}

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "NonLinearShaper");
    // add "Cubic" double spin box
    AddDoubleSpinBox(Box, Parent, {"Cubic", 0.0, -10.0, 10.0, 0.01, 3}, [&Controller](double Value){ Controller.OnNonLinearShaperA(Value); });
    // add "Quadratic" double spin box
    AddDoubleSpinBox(Box, Parent, {"Quadratic", 0.0, -10.0, 10.0, 0.01, 3}, [&Controller](double Value){ Controller.OnNonLinearShaperB(Value); });
    // add "PreGain" double spin box
    AddDoubleSpinBox(Box, Parent, {"PreGain", 1.0, 0.0, 10.0, 0.01, 3}, [&Controller](double Value){ Controller.OnNonLinearShaperPreGain(Value); });
}

void AddBitFX(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "BitFX");
    AddSpinBox(Box, Parent, {"BitCrusher", 0, 0, 15, 1}, [&Controller](int Value){ Controller.OnBitCrusherDepth(Value); });
    AddSpinBox(Box, Parent, {"S n H", 0, 0, 1024, 1}, [&Controller](int Value){ Controller.OnSampleAndHoldPeriod(Value); });
    AddSpinBox(Box, Parent, {"Rippler", 0, 0, 255, 1}, [&Controller](int Value){ Controller.OnRipplerStrength(Value); });
}



}
