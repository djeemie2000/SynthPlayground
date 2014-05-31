#ifndef GUIITEMS_H
#define GUIITEMS_H


class QGroupBox;
class QWidget;
class IStepSequencer;
class IBitFx;
class IWaveFolder;
class ILPFilter;
class INonLinearShaper;
class ICombinedOperatorStage;
class ICombinedFoldedOperatorStage;

namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, IWaveFolder& Controller);

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, ILPFilter& Controller);

void AddNonLinearShaper(QGroupBox *GroupBox, QWidget *Parent, INonLinearShaper& Controller);

void AddBitFX(QGroupBox *GroupBox, QWidget *Parent, IBitFx& Controller);

void AddStepSequencer(QGroupBox *GroupBox, QWidget *Parent, IStepSequencer& Controller);

void AddCombinedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedOperatorStage& Controller);

void AddCombinedFoldedOperatorStage(QGroupBox *GroupBox, QWidget *Parent, ICombinedFoldedOperatorStage& Controller);


}

#endif // GUIITEMS_H
