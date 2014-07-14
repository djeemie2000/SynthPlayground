#ifndef GUIITEMS_H
#define GUIITEMS_H

#include <string>

class QGroupBox;
class QWidget;
class IStepSequencer;
class IBitFx;
class IWaveFolder;
class ILPFilter;
class INonLinearShaper;
class ICombinedOperatorStage;
class ICombinedFoldedOperatorStage;
class ILFOBank;
class CCommandStackController;

namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, IWaveFolder& Controller);
void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, ILPFilter& Controller);
void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, INonLinearShaper& Controller);
void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddBitFX(QGroupBox *GroupBox, QWidget *Parent, IBitFx& Controller);

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, IStepSequencer& Controller);
void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, int NumSteps, const std::string& Name, CCommandStackController& Controller);


void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedOperatorStage& Controller);
void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedFoldedOperatorStage& Controller);
void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddFMOperatorStage(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddInterpolatingOperator(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);


void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, ILFOBank& LFOBank);
void AddLFOBank(QGroupBox *GroupBox, QWidget *Parent, int LFOBankSize, const std::string& Name, CCommandStackController& Controller);

void AddAREnvelope(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddFeedbackDelay(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);

void AddMasterVolume(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name, CCommandStackController& Controller);


}

#endif // GUIITEMS_H
