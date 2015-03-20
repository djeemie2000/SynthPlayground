#ifndef GUIITEMS_H
#define GUIITEMS_H

#include <string>
#include <vector>

class QGroupBox;
class QWidget;
class CCommandStackController;

namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, int MaxNumSteps, const std::string& Name, CCommandStackController& Controller);

void AddRingSequencer(QGroupBox *GroupBox, QWidget *Parent, int MaxNumSteps, const std::string& Name, CCommandStackController& Controller);

void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddFMOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddInterpolatingOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddSimpleInterpolatingOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddDCOffsetOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddIntegerPowerShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddDistortion(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddPosNegShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, int LFOBankSize, const std::string& Name, CCommandStackController& Controller);
void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, const std::vector<std::string>& LFONames, const std::string& Name, CCommandStackController& Controller);

void AddEnvelopeBank(QGroupBox *GroupBox, QWidget *Parent, const std::vector<std::string>& EnvelopeNames, const std::string& Name, CCommandStackController& Controller);

void AddModulation(QGroupBox *GroupBox, QWidget *Parent, const std::vector<std::string>& ModulatorNames, const std::string& Name, CCommandStackController& Controller);

void AddAREnvelope(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddFeedbackDelay(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddMasterVolume(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);


}

#endif // GUIITEMS_H
