#include "GuiUtilities.h"
#include <QDoubleSpinBox>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QLayout>
#include "QGuiCallbacks.h"

namespace guiutils
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

void AddDoubleSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SDoubleSpinboxProperties &Properties, DoubleValueChangedCallbackType Callback)
{
    QDoubleSpinBox* SpinBox = AddDoubleSpinBox(GroupBox, Parent, Properties);

    QDoubleValueChanged* CallbackHandler = new QDoubleValueChanged(Callback, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(double)), CallbackHandler, SLOT(OnValueChanged(double)));
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

void AddSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SSpinboxProperties &Properties, IntValueChangedCallbackType Callback)
{
    QSpinBox* SpinBox = AddSpinBox(GroupBox, Parent, Properties);

    QIntValueChanged* CallbackHandler = new QIntValueChanged(Callback, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(int)), CallbackHandler, SLOT(OnValueChanged(int)));
}


}
