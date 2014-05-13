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



}
