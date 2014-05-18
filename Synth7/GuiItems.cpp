#include "GuiItems.h"
#include "GuiUtilities.h"
#include <QGroupBox>
#include <QGridLayout>
#include "Notes.h"
#include "Controller.h"
#include "SelectableCombinorFactory.h"
#include "SelectableOperatorFactory.h"

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

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{    
    QGroupBox* Box = new QGroupBox("StepSequencer", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 1, "Bpm");
    AddLabel(Layout, Parent, 0, 2, "Beats");

    // 1,0 Btn on/off
    AddSmallButton(Layout, Parent, 1, 0, "Go", [&Controller](bool Value){ if(Value){ Controller.Start(); } else { Controller.Stop(); } });
    // 1,1 doublespinbox bpm
    AddDoubleSpinBox(Layout, Parent, 1, 1, {"", 120.0, 1.0, 240.0, 0.1, 1}, [&Controller](double Value){ Controller.OnNonLinearShaperA(Value); });
    // 1,2 spinbox beats
    AddSpinBox(Layout, Parent, 1, 2, {"", 2, 1, 16, 1}, [&Controller](int Value){Controller.SetBarsPerBeat(Value); } );

    AddLabel(Layout, Parent, 2, 0, "Octave");
    AddLabel(Layout, Parent, 2, 1, "Note");
    AddLabel(Layout, Parent, 2, 2, "Active");

    for(int Step = 0; Step<Controller.NumSteps(); ++Step)
    {
        // Step,0 spinbox octave
        AddSpinBox(Layout, Parent, 4+Step, 0, {"", 2, 0, 8, 1}, [&Controller,Step](int Value){ Controller.SetOctave(Step, static_cast<EOctave>(Value)); });
        // Step,1 combibox note
        AddComboBox(Layout, Parent, 4+Step, 1, {"", NoteList(), static_cast<int>(ENote::A)}, [&Controller,Step](int Value){ Controller.SetNote(Step, static_cast<ENote>(Value)); });
        // Step,2 tool button active on/off
        AddSmallButton(Layout, Parent, 4+Step, 2, "On", [&Controller,Step](bool Value){ Controller.SetActive(Step, Value); });
    }


    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

void AddOperatorStage(QGroupBox *GroupBox, QWidget *Parent, CController &Controller)
{
    QGroupBox* Box = new QGroupBox("Operator", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 0, "Combinor");
    AddComboBox(Layout, Parent, 0, 1, {"", CSelectableCombinorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnCombinor(Value); });
    AddSmallButton(Layout, Parent, 0, 2, "Sync", [&Controller](){ Controller.OnSync(); });

    AddDoubleSpinBox(Layout, Parent, 1, 0, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(0, Value); });
    AddLabel(Layout, Parent, 1, 1, "Amplitude");
    AddDoubleSpinBox(Layout, Parent, 1, 2, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(1, Value); });

    AddComboBox(Layout, Parent, 2, 0, {"", CSelectableOperatorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnOperator(0, Value); });
    AddLabel(Layout, Parent, 2, 1, "Operator");
    AddComboBox(Layout, Parent, 2, 2, {"", CSelectableOperatorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnOperator(1, Value); });

    AddDoubleSpinBox(Layout, Parent, 3, 0, {"", 1.0, 0.0, 32.0, 0.001, 4}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(0, Value); });
    AddLabel(Layout, Parent, 3, 1, "Freq Multiplier");
    AddDoubleSpinBox(Layout, Parent, 3, 2, {"", 1.0, 0.0, 32.0, 0.001, 4}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(1, Value); });

    AddDoubleSpinBox(Layout, Parent, 4, 0, {"", 0.0, 0.0, 1.0, 0.001, 3}, [&Controller](double Value){ Controller.OnPhaseshift(0, Value); });
    AddLabel(Layout, Parent, 4, 1, "Phase Shift");
    AddDoubleSpinBox(Layout, Parent, 4, 2, {"", 0.0, 0.0, 1.0, 0.001, 3}, [&Controller](double Value){ Controller.OnPhaseshift(1, Value); });

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

}
