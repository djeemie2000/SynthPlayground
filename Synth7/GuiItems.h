#ifndef GUIITEMS_H
#define GUIITEMS_H


class QGroupBox;
class QWidget;
class CController;
namespace guiutils
{

void AddWaveFolder(QGroupBox *GroupBox, QWidget *Parent, CController& Controller);

void AddLPFilter(QGroupBox *GroupBox, QWidget *Parent, CController& Controller);


}

#endif // GUIITEMS_H
