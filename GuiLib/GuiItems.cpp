#include "GuiItems.h"
#include "GuiUtilities.h"
#include <QGroupBox>
#include <QGridLayout>
#include "Notes.h"
#include "StepSequencerI.h"
#include "BitFxI.h"
#include "WaveFolderI.h"
#include "LPFilterI.h"
#include "NonLinearShaperI.h"
#include "CombinedOperatorStageI.h"
#include "SelectableCombinorFactory.h"
#include "SelectableOperatorFactory.h"
#include "CombinedFoldedOperatorStageI.h"
#include "LFOBankI.h"
#include "CommandStackController.h"

namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, IWaveFolder &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "WaveFolder");
    // -> add "Fold" doublespinbox
    AddDoubleSpinBox(Box, Parent, {"Fold", 0.97, 0, 1, 0.01, 2}, [&Controller](double Value){ Controller.OnWaveFold(Value); });
}

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "WaveFolder");
    // -> add "Fold" doublespinbox
    AddDoubleSpinBox(Box, Parent, {"Fold", 0.97, 0, 1, 0.01, 2}, Name+"/Fold", Controller);
}

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, ILPFilter &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "LPFilter");
    // add "Cutoff" double spin box
    AddDoubleSpinBox(Box, Parent, {"CutOff", 1.0, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnLPFilterCutoff(Value); });
    // add "Poles" int spin box
    AddSpinBox(Box, Parent, {"Poles", 1, 1, 24, 1}, [&Controller](int Value){ Controller.OnLPFilterPoles(Value); });
    // add "Q" double spin box
    AddDoubleSpinBox(Box, Parent, {"Q", 0.0, -1.0, 2.0, 0.01, 3}, [&Controller](double Value){ Controller.OnLPFilterFeedback(Value); });
}

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "LPFilter");
    // add "Cutoff" double spin box
    AddDoubleSpinBox(Box, Parent, {"CutOff", 1.0, 0.0, 1.0, 0.01, 2}, Name+"/Cutoff", Controller);
    // add "Poles" int spin box
    AddSpinBox(Box, Parent, {"Poles", 1, 1, 24, 1}, Name+"/Poles", Controller);
    // add "Q" double spin box
    AddDoubleSpinBox(Box, Parent, {"Q", 0.0, -1.0, 2.0, 0.01, 3}, Name+"/Q", Controller);
}

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, INonLinearShaper &Controller)
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

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "NonLinearShaper");
    // add "Cubic" double spin box
    AddDoubleSpinBox(Box, Parent, {"Cubic", 0.0, -10.0, 10.0, 0.01, 3}, Name+"/Cubic", Controller);
    // add "Quadratic" double spin box
    AddDoubleSpinBox(Box, Parent, {"Quadratic", 0.0, -10.0, 10.0, 0.01, 3}, Name+"/Quadratic", Controller);
    // add "PreGain" double spin box
    AddDoubleSpinBox(Box, Parent, {"PreGain", 1.0, 0.0, 10.0, 0.01, 3}, Name+"/PreGain", Controller);
}

void AddBitFX(QGroupBox *GroupBox, QWidget *Parent, IBitFx &Controller)
{
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "BitFX");
    AddSpinBox(Box, Parent, {"BitCrusher", 0, 0, 15, 1}, [&Controller](int Value){ Controller.OnBitCrusherDepth(Value); });
    AddSpinBox(Box, Parent, {"S n H", 0, 0, 1024, 1}, [&Controller](int Value){ Controller.OnSampleAndHoldPeriod(Value); });
    AddSpinBox(Box, Parent, {"Rippler", 0, 0, 255, 1}, [&Controller](int Value){ Controller.OnRipplerStrength(Value); });
}

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, IStepSequencer &Controller)
{    
    QGroupBox* Box = new QGroupBox("StepSequencer", Parent);
    QGridLayout* Layout = new QGridLayout();

    // spinbox for num steps
    AddSpinBox(Layout, Parent, 0, 0, {"", Controller.GetMaxNumSteps(), 1, Controller.GetMaxNumSteps(), 1}, [&Controller](int Value){Controller.SetNumSteps(Value); } );
    AddLabel(Layout, Parent, 0, 1, "Bpm");
    AddLabel(Layout, Parent, 0, 2, "Beats");

    // 1,0 Btn on/off
    AddSmallButton(Layout, Parent, 1, 0, "Go", [&Controller](bool Value){ if(Value){ Controller.Start(); } else { Controller.Stop(); } });
    // 1,1 doublespinbox bpm
    AddDoubleSpinBox(Layout, Parent, 1, 1, {"", 120.0, 1.0, 240.0, 0.1, 1}, [&Controller](double Value){ Controller.SetBeatsPerMinute(Value); });
    // 1,2 spinbox beats
    AddSpinBox(Layout, Parent, 1, 2, {"", 2, 1, 16, 1}, [&Controller](int Value){Controller.SetBarsPerBeat(Value); } );

    AddLabel(Layout, Parent, 2, 0, "Octave");
    AddLabel(Layout, Parent, 2, 1, "Note");
    AddLabel(Layout, Parent, 2, 2, "Active");

    for(int Step = 0; Step<Controller.GetMaxNumSteps(); ++Step)
    {
        // Step,0 spinbox octave
        AddSpinBox(Layout, Parent, 4+Step, 0, {"", 2, 0, 8, 1}, [&Controller,Step](int Value){ Controller.SetOctave(Step, static_cast<EOctave>(Value)); });
        // Step,1 combibox note
        AddComboBox(Layout, Parent, 4+Step, 1, {"", { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" }/*CNoteList::Create()*/, static_cast<int>(ENote::A)}, [&Controller,Step](int Value){ Controller.SetNote(Step, static_cast<ENote>(Value)); });
        // Step,2 tool button active on/off
        AddSmallButton(Layout, Parent, 4+Step, 2, "On", [&Controller,Step](bool Value){ Controller.SetActive(Step, Value); });
    }


    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, int MaxNumSteps, const std::string& Name, CCommandStackController& Controller)
{
    QGroupBox* Box = new QGroupBox("StepSequencer", Parent);
    QGridLayout* Layout = new QGridLayout();

    // 1,0 Btn on/off
    AddCheckableSmallButton(Layout, Parent, 0, 0, "Go", Name+"/Go", Controller);
    AddLabel(Layout, Parent, 0, 1, "Steps");
    // spinbox for num steps
    AddSpinBox(Layout, Parent, 0, 2, {"", MaxNumSteps, 1, MaxNumSteps, 1}, Name+"/NumSteps", Controller );

    AddLabel(Layout, Parent, 1, 0, "Duration");
    AddLabel(Layout, Parent, 1, 1, "Bpm");
    AddLabel(Layout, Parent, 1, 2, "Beats");

    // 1,0 doublespinbox bpm
    AddSpinBox(Layout, Parent, 2, 0, {"", 100, 1, 100, 1}, Name+"/Duration", Controller);
    // 1,1 doublespinbox bpm
    AddDoubleSpinBox(Layout, Parent, 2, 1, {"", 120.0, 1.0, 240.0, 0.1, 1}, Name+"/BeatsPerMinute", Controller);
    // 1,2 spinbox beats
    AddSpinBox(Layout, Parent, 2, 2, {"", 2, 1, 16, 1}, Name+"/BarsPerBeat", Controller);

    AddLabel(Layout, Parent, 3, 0, "Octave");
    AddLabel(Layout, Parent, 3, 1, "Note");
    AddLabel(Layout, Parent, 3, 2, "Active");

    for(int Step = 0; Step<MaxNumSteps; ++Step)
    {
        // Step,0 spinbox octave
        AddSpinBox(Layout, Parent, 4+Step, 0, {"", 2, 0, 8, 1}, Name+"/Octave/"+std::to_string(Step), Controller);
        // Step,1 combibox note
        AddComboBox(Layout, Parent, 4+Step, 1, {"", { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" }/*CNoteList::Create()*/, static_cast<int>(ENote::A)}, Name+"/Note/"+std::to_string(Step), Controller);
        // Step,2 tool button active on/off
        AddCheckableSmallButton(Layout, Parent, 4+Step, 2, "On", Name+"/Active/"+std::to_string(Step), Controller);
    }

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}


void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedOperatorStage &Controller)
{
    QGroupBox* Box = new QGroupBox("Operator", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 0, "Combinor");
    AddComboBox(Layout, Parent, 0, 1, {"", CSelectableCombinorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnCombinor(Value); });
    AddSmallButton(Layout, Parent, 0, 2, "Sync", [&Controller](){ Controller.OnSync(); });

    AddDoubleSpinBox(Layout, Parent, 1, 0, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnAmplitude(0, Value); });
    AddLabel(Layout, Parent, 1, 1, "Amplitude");
    AddDoubleSpinBox(Layout, Parent, 1, 2, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnAmplitude(1, Value); });

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

void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    QGroupBox* Box = new QGroupBox("Operator", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 0, "Combinor");
    AddComboBox(Layout, Parent, 0, 1, {"", CSelectableCombinorFactory::SelectionList(), 0 }, Name+"/Combinor", Controller);
    AddSmallButton(Layout, Parent, 0, 2, "Sync", Name+"/Sync", Controller);

    AddDoubleSpinBox(Layout, Parent, 1, 0, {"", 0.5, 0.0, 1.0, 0.01, 2}, Name+"/Amplitude/0", Controller);
    AddLabel(Layout, Parent, 1, 1, "Amplitude");
    AddDoubleSpinBox(Layout, Parent, 1, 2, {"", 0.5, 0.0, 1.0, 0.01, 2}, Name+"/Amplitude/1", Controller);

    AddComboBox(Layout, Parent, 2, 0, {"", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator/0", Controller);
    AddLabel(Layout, Parent, 2, 1, "Operator");
    AddComboBox(Layout, Parent, 2, 2, {"", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator/1", Controller);

    AddDoubleSpinBox(Layout, Parent, 3, 0, {"", 1.0, 0.0, 32.0, 0.001, 4}, Name+"/FrequencyMultiplier/0", Controller);
    AddLabel(Layout, Parent, 3, 1, "Freq Multiplier");
    AddDoubleSpinBox(Layout, Parent, 3, 2, {"", 1.0, 0.0, 32.0, 0.001, 4}, Name+"/FrequencyMultiplier/1", Controller);

    AddDoubleSpinBox(Layout, Parent, 4, 0, {"", 0.0, 0.0, 1.0, 0.001, 3}, Name+"/PhaseShift/0", Controller);
    AddLabel(Layout, Parent, 4, 1, "Phase Shift");
    AddDoubleSpinBox(Layout, Parent, 4, 2, {"", 0.0, 0.0, 1.0, 0.001, 3}, Name+"/PhaseShift/1", Controller);

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}


void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedFoldedOperatorStage &Controller)
{
    QGroupBox* Box = new QGroupBox("Operator", Parent);
    QGridLayout* Layout = new QGridLayout();

    int GridX = 0;
    AddLabel(Layout, Parent, GridX, 0, "Combinor");
    AddComboBox(Layout, Parent, GridX, 1, {"", CSelectableCombinorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnCombinor(Value); });
    AddSmallButton(Layout, Parent, GridX, 2, "Sync", [&Controller](){ Controller.OnSync(); });

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnAmplitude(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "Amplitude");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.5, 0.0, 1.0, 0.01, 2}, [&Controller](double Value){ Controller.OnAmplitude(1, Value); });

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.97, 0.0, 1.0, 0.01, 3}, [&Controller](double Value){ Controller.OnFold(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "Fold");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.97, 0.0, 1.0, 0.01, 3}, [&Controller](double Value){ Controller.OnFold(1, Value); });

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.0, -1.0, 1.0, 0.01, 3}, [&Controller](double Value){ Controller.OnFoldModAmount(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "FoldModAmt");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.0, -1.0, 1.0, 0.01, 3}, [&Controller](double Value){ Controller.OnFoldModAmount(1, Value); });

    ++GridX;
    AddComboBox(Layout, Parent, GridX, 0, {"", CSelectableOperatorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnOperator(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "Operator");
    AddComboBox(Layout, Parent, GridX, 2, {"", CSelectableOperatorFactory::SelectionList(), 0 }, [&Controller](int Value){ Controller.OnOperator(1, Value); });

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 1.0, 0.0, 32.0, 0.001, 4}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "Freq Multiplier");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 1.0, 0.0, 32.0, 0.001, 4}, [&Controller](double Value){ Controller.OnFrequencyMultiplier(1, Value); });

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.0, 0.0, 1.0, 0.001, 3}, [&Controller](double Value){ Controller.OnPhaseshift(0, Value); });
    AddLabel(Layout, Parent, GridX, 1, "Phase Shift");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.0, 0.0, 1.0, 0.001, 3}, [&Controller](double Value){ Controller.OnPhaseshift(1, Value); });

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    QGroupBox* Box = new QGroupBox("Operator", Parent);
    QGridLayout* Layout = new QGridLayout();

    int GridX = 0;
    AddLabel(Layout, Parent, GridX, 0, "Combinor");
    AddComboBox(Layout, Parent, GridX, 1, {"", CSelectableCombinorFactory::SelectionList(), 0 }, Name+"/Combinor", Controller);
    AddSmallButton(Layout, Parent, GridX, 2, "Sync", Name+"/Sync", Controller);

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.5, 0.0, 1.0, 0.01, 2}, Name+"/Amplitude/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "Amplitude");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.5, 0.0, 1.0, 0.01, 2}, Name+"/Amplitude/1", Controller);

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.97, 0.0, 1.0, 0.01, 3}, Name+"/Fold/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "Fold");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.97, 0.0, 1.0, 0.01, 3}, Name+"/Fold/1", Controller);

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/FoldModAmt/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "FoldModAmt");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/FoldModAmt/1", Controller);

    ++GridX;
    AddComboBox(Layout, Parent, GridX, 0, {"", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "Operator");
    AddComboBox(Layout, Parent, GridX, 2, {"", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator/1", Controller);

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 1.0, 0.0, 32.0, 0.001, 4}, Name+"/FrequencyMultiplier/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "Freq Multiplier");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 1.0, 0.0, 32.0, 0.001, 4}, Name+"/FrequencyMultiplier/1", Controller);

    ++GridX;
    AddDoubleSpinBox(Layout, Parent, GridX, 0, {"", 0.0, 0.0, 1.0, 0.001, 3}, Name+"/PhaseShift/0", Controller);
    AddLabel(Layout, Parent, GridX, 1, "Phase Shift");
    AddDoubleSpinBox(Layout, Parent, GridX, 2, {"", 0.0, 0.0, 1.0, 0.001, 3}, Name+"/PhaseShift/1", Controller);

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

void AddFMOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "FMOperator");
    AddLabel(Box, Parent, "Oscillator");
    AddComboBox(Box, Parent, {"Oscillator", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Oscillator/Select", Controller);

    AddLabel(Box, Parent, "Modulator");
    AddComboBox(Box, Parent, {"Modulator", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Modulator/Select", Controller);
    AddDoubleSpinBox(Box, Parent, {"Amplitude", 0.0, 0, 1.0, 0.01, 3}, Name+"/Modulator/Amplitude", Controller);
    AddDoubleSpinBox(Box, Parent, {"AmplitudeModAmt", 0.0, 0, 1.0, 0.01, 3}, Name+"/Modulator/AmplitudeModAmt", Controller);
    AddDoubleSpinBox(Box, Parent, {"Freq Multiplier", 1.0, 0, 32.0, 0.001, 4}, Name+"/Modulator/FrequencyMultiplier", Controller);
    AddDoubleSpinBox(Box, Parent, {"Phase Shift", 0.0, 0, 2.0, 0.001, 3}, Name+"/Modulator/PhaseShift", Controller);

    AddLabel(Box, Parent, "Carrier");
    AddComboBox(Box, Parent, {"Carrier", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Carrier/Select", Controller);
}

void AddInterpolatingOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Oscillator");
    AddComboBox(Box, Parent, {"Operator1", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator1/Select", Controller);
    AddComboBox(Box, Parent, {"Operator2", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator2/Select", Controller);

    AddDoubleSpinBox(Box, Parent, {"Mix", 0.0, 0, 1.0, 0.01, 3}, Name+"/Mix", Controller);
    AddDoubleSpinBox(Box, Parent, {"MixModAmt", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/MixModAmt", Controller);

    AddDoubleSpinBox(Box, Parent, {"Skew", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/Skew", Controller);
    AddDoubleSpinBox(Box, Parent, {"SkewModAmt", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/SkewModAmt", Controller);
}

void AddSimpleInterpolatingOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Oscillator");
    AddComboBox(Box, Parent, {"Operator1", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator1/Select", Controller);
    AddComboBox(Box, Parent, {"Operator2", CSelectableOperatorFactory::SelectionList(), 0 }, Name+"/Operator2/Select", Controller);

    AddDoubleSpinBox(Box, Parent, {"Mix", 0.0, 0, 1.0, 0.01, 3}, Name+"/Mix", Controller);
    AddDoubleSpinBox(Box, Parent, {"Skew", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/Skew", Controller);
}


void AddDCOffsetOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "DC");

    AddDoubleSpinBox(Box, Parent, {"Offset", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/Offset", Controller);
    AddDoubleSpinBox(Box, Parent, {"ModAmt", 0.0, -1.0, 1.0, 0.01, 3}, Name+"/OffsetModAmt", Controller);
}

void AddIntegerPowerShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Shaper");

    AddDoubleSpinBox(Box, Parent, {"Strength", 0.0, 0.0, 1.0, 0.01, 3}, Name+"/Strength", Controller);
    AddSpinBox(Box, Parent, {"Power", 4, 1, 64, 1}, Name+"/Power", Controller);
    AddDoubleSpinBox(Box, Parent, {"PreGain", 0.0, 0.0, 1.0, 0.01, 3}, Name+"/PreGain", Controller);
}

void AddDistortion(QGroupBox *GroupBox, QWidget *Parent, const string &Name, CCommandStackController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Distortion");

    AddDoubleSpinBox(Box, Parent, {"Drive", 0.0, 0.0, 1.0, 0.01, 3}, Name+"/Drive", Controller);
}

void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, ILFOBank &LFOBank)
{
    QGroupBox* Box = new QGroupBox("LFOBank", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 0, "Freq");
    AddLabel(Layout, Parent, 1, 0, "Shape");

    for(int idxLFO = 0; idxLFO<LFOBank.LFOBankSize(); ++idxLFO)
    {
        // add "Frequency" double spin box
        AddDoubleSpinBox(Layout, Parent, 0, idxLFO+1, {"", 1.0, 0.01, 44100.0, 0.1, 2}, [&LFOBank,idxLFO](double Value){ LFOBank.SetLFOFrequency(idxLFO, Value); });
        // add waveform selection
        AddComboBox(Layout, Parent, 1, idxLFO+1, {"", CSelectableOperatorFactory::SelectionList(), 3 }, [&LFOBank,idxLFO](int Value){ LFOBank.SelectLFOWaveform(idxLFO, Value); });
    }

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}



void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, int LFOBankSize, const std::string& Name, CCommandStackController &Controller)
{
    QGroupBox* Box = new QGroupBox("LFOBank", Parent);
    QGridLayout* Layout = new QGridLayout();

    AddLabel(Layout, Parent, 0, 0, "Freq");
    AddLabel(Layout, Parent, 1, 0, "Shape");

    for(int idxLFO = 0; idxLFO<LFOBankSize; ++idxLFO)
    {
        // add "Frequency" double spin box
        AddDoubleSpinBox(Layout, Parent, 0, idxLFO+1, {"", 1.0, 0.01, 44100.0, 0.1, 2}, Name+"/"+std::to_string(idxLFO)+"/Frequency", Controller);
        // add waveform selection
        AddComboBox(Layout, Parent, 1, idxLFO+1, {"", CSelectableOperatorFactory::SelectionList(), 3 }, Name+"/"+std::to_string(idxLFO)+"/Waveform", Controller);
    }

    Box->setLayout(Layout);
    GroupBox->layout()->addWidget(Box);
}

void AddAREnvelope(QGroupBox *GroupBox, QWidget *Parent, const string &Name, CCommandStackController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "AREnvelope");
    // add "attack" double spin box
    AddDoubleSpinBox(Box, Parent, {"Attack", 10.0, 0.0, 10000.0, 1.0, 1}, Name+"/AttackMilliSeconds", Controller);
    // add "release" double spin box
    AddDoubleSpinBox(Box, Parent, {"Release", 20.0, 0.0, 10000.0, 1.0, 1}, Name+"/ReleaseMilliSeconds", Controller);
}

void AddFeedbackDelay(QGroupBox *GroupBox, QWidget *Parent, const string &Name, CCommandStackController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Delay");
    // add "WetDry" double spin box
    AddCheckableSmallButton(Box, Parent, "Bypass", Name+"/Bypass", Controller);
    // add "WetDry" double spin box
    AddDoubleSpinBox(Box, Parent, {"WetDry", 0.0, 0.0, 1.0, 0.01, 3}, Name+"/WetDry", Controller);
    // add "Delay" double spin box
    AddDoubleSpinBox(Box, Parent, {"Delay", 250.0, 0.0, 5000.0, 1, 1}, Name+"/DelayMilliSeconds", Controller);
    // add "Feedback" double spin box
    AddDoubleSpinBox(Box, Parent, {"Feedback", 500.0, 0.0, 1.0, 0.01, 3}, Name+"/Feedback", Controller);
}

void AddMasterVolume(QGroupBox *GroupBox, QWidget *Parent, const string &Name, CCommandStackController &Controller)
{
    // add child groupbox
    QGroupBox* Box = AddGroupBox(GroupBox, Parent, "Master");
    // add "Volume" double spin box
    AddDoubleSpinBox(Box, Parent, {"Volume", 1.0, 0.0, 1.0, 0.01, 3}, Name, Controller);
}

}
