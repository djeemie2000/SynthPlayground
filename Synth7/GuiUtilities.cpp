#include "GuiUtilities.h"
#include <QDoubleSpinBox>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QLayout>

namespace guiutilities
{

QDoubleSpinBox *AddDoubleSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SDoubleSpinboxProperties &Properties)
{
    // add label with name
    GroupBox->layout()->addWidget(new QLabel(QString::fromStdString(Properties.s_Name), Parent));

    // create spingbox, apply properties, and add to groupbox
    QDoubleSpinBox* SpinBox = new QDoubleSpinBox(Parent);
    SpinBox->setMinimum(Properties.s_Min);
    SpinBox->setMaximum(Properties.s_Max);
    SpinBox->setValue(Properties.s_Default);
    SpinBox->setSingleStep(Properties.s_Step);
    SpinBox->setDecimals(Properties.s_NumDecimals);
    GroupBox->layout()->addWidget(SpinBox);

    return SpinBox;
}

QSpinBox *AddSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SSpinboxProperties &Properties)
{
    // add label with name
    GroupBox->layout()->addWidget(new QLabel(QString::fromStdString(Properties.s_Name), Parent));

    // create spingbox, apply properties, and add to groupbox
    QSpinBox* SpinBox = new QSpinBox(Parent);
    SpinBox->setMinimum(Properties.s_Min);
    SpinBox->setMaximum(Properties.s_Max);
    SpinBox->setValue(Properties.s_Default);
    SpinBox->setSingleStep(Properties.s_Step);
    GroupBox->layout()->addWidget(SpinBox);

    return SpinBox;
}



}
