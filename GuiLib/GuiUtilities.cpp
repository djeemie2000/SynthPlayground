#include "GuiUtilities.h"
#include <QDoubleSpinBox>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QToolButton>
#include <QComboBox>
#include "QGuiCallbacks.h"
#include "GuiCommandStack.h"

namespace guiutils
{

QGroupBox *AddGroupBox(QGroupBox *GroupBox, QWidget *Parent, const std::string &Name)
{
    QGroupBox* ChildBox = new QGroupBox(QString::fromStdString(Name), Parent);
    ChildBox->setLayout(new QHBoxLayout());
    GroupBox->layout()->addWidget(ChildBox);
    return ChildBox;
}

void AddLabel(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name)
{
    if(!Name.empty())
    {
        GroupBox->layout()->addWidget(new QLabel(QString::fromStdString(Name), Parent));
    }
}

void AddLabel(QGridLayout *Layout, QWidget *Parent, int X, int Y, const std::string &Name)
{
    if(!Name.empty())
    {
        Layout->addWidget(new QLabel(QString::fromStdString(Name), Parent), Y, X);
    }
}

QToolButton* CreateToolButton(QWidget* Parent, const std::string& Name, bool Checkable)
{
    QToolButton* Button = new QToolButton(Parent);
    Button->setText(QString::fromStdString(Name));
    Button->setCheckable(Checkable);
    return Button;
}

void AddCallback(QToolButton* Button, QWidget* Parent, SimpleCallbackType Callback)
{
    QSomethingHappened* CallbackHandler = new QSomethingHappened(Callback, Parent);
    Parent->connect(Button, SIGNAL(clicked()), CallbackHandler, SLOT(OnSomethingHappened()));
}

void AddCallback(QToolButton* Button, QWidget* Parent, BoolValueChangedCallbackType Callback)
{
    QBoolValueChanged* CallbackHandler = new QBoolValueChanged(Callback, Parent);
    Parent->connect(Button, SIGNAL(clicked(bool)), CallbackHandler, SLOT(OnValueChanged(bool)));
}

void AddSmallButton(QGridLayout *Layout, QWidget *Parent, int X, int Y, const std::string &Name, SimpleCallbackType Callback)
{
    QToolButton* Button = CreateToolButton(Parent, Name, false);
    AddCallback(Button, Parent, Callback);
    Layout->addWidget(Button, Y, X);
}

void AddSmallButton(QGridLayout* Layout, QWidget *Parent, int X, int Y, const std::string& Name, const std::string& ParameterName, CCommandStackController& Controller)
{
    QToolButton* Button = CreateToolButton(Parent, Name, false);
    ConnectCheckableToolButton(Button, Parent, ParameterName, Controller);
    Layout->addWidget(Button, Y, X);
}


void AddSmallButton(QGridLayout *Layout, QWidget *Parent, int X, int Y, const std::string &Name, BoolValueChangedCallbackType Callback)
{
    QToolButton* Button = CreateToolButton(Parent, Name, true);
    AddCallback(Button, Parent, Callback);
    Layout->addWidget(Button, Y, X);
}

void AddCheckableSmallButton(QGridLayout *Layout, QWidget *Parent, int X, int Y, const std::string &Name, const std::string &ParameterName, CCommandStackController &Controller)
{
    QToolButton* Button = CreateToolButton(Parent, Name, true);
    ConnectCheckableToolButton(Button, Parent, ParameterName, Controller);
    Layout->addWidget(Button, Y, X);
}

void AddCheckableSmallButton(QGroupBox *GroupBox, QWidget *Parent, const std::string &Name, const std::string &ParameterName, CCommandStackController &Controller)
{
    QToolButton* Button = CreateToolButton(Parent, Name, true);
    ConnectCheckableToolButton(Button, Parent, ParameterName, Controller);
    GroupBox->layout()->addWidget(Button);
}

QDoubleSpinBox* CreateDoubleSpinBox(QWidget* Parent, const SDoubleSpinboxProperties &Properties)
{
    // create spingbox, apply properties
    QDoubleSpinBox* SpinBox = new QDoubleSpinBox(Parent);
    SpinBox->setMinimum(Properties.s_Min);
    SpinBox->setMaximum(Properties.s_Max);
    SpinBox->setValue(Properties.s_Default);
    SpinBox->setSingleStep(Properties.s_Step);
    SpinBox->setDecimals(Properties.s_NumDecimals);
    return SpinBox;
}

void AddCallback(QDoubleSpinBox* SpinBox, QWidget* Parent, DoubleValueChangedCallbackType Callback)
{
    QDoubleValueChanged* CallbackHandler = new QDoubleValueChanged(Callback, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(double)), CallbackHandler, SLOT(OnValueChanged(double)));
}

void AddDoubleSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SDoubleSpinboxProperties &Properties, DoubleValueChangedCallbackType Callback)
{
    // add label with name
    AddLabel(GroupBox, Parent, Properties.s_Name);

    // create spingbox, apply properties, add to groupbox, add Callback
    QDoubleSpinBox* SpinBox = CreateDoubleSpinBox(Parent, Properties);
    GroupBox->layout()->addWidget(SpinBox);
    AddCallback(SpinBox, Parent, Callback);
}

void AddDoubleSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SDoubleSpinboxProperties& Properties, const std::string& ParameterName, CCommandStackController& Controller)
{
    // add label with name
    AddLabel(GroupBox, Parent, Properties.s_Name);

    // create spingbox, apply properties, add to groupbox, add Callback
    QDoubleSpinBox* SpinBox = CreateDoubleSpinBox(Parent, Properties);
    GroupBox->layout()->addWidget(SpinBox);
    ConnectDoubleSpinbox(SpinBox, Parent, ParameterName, Controller);
}

void AddDoubleSpinBox(QGridLayout *Layout, QWidget *Parent, int X, int Y, const SDoubleSpinboxProperties &Properties, DoubleValueChangedCallbackType Callback)
{
    QDoubleSpinBox* SpinBox = CreateDoubleSpinBox(Parent, Properties);
    Layout->addWidget(SpinBox, Y, X);
    AddCallback(SpinBox, Parent, Callback);
}

void AddDoubleSpinBox(QGridLayout* Layout, QWidget * Parent, int X, int Y, const SDoubleSpinboxProperties& Properties, const std::string& ParameterName, CCommandStackController& Controller)
{
    QDoubleSpinBox* SpinBox = CreateDoubleSpinBox(Parent, Properties);
    Layout->addWidget(SpinBox, Y, X);
    ConnectDoubleSpinbox(SpinBox, Parent, ParameterName, Controller);
}


QSpinBox *CreateSpinBox(QWidget *Parent, const SSpinboxProperties &Properties)
{
    // create spingbox, apply properties,
    QSpinBox* SpinBox = new QSpinBox(Parent);
    SpinBox->setMinimum(Properties.s_Min);
    SpinBox->setMaximum(Properties.s_Max);
    SpinBox->setValue(Properties.s_Default);
    SpinBox->setSingleStep(Properties.s_Step);
    return SpinBox;
}

void AddCallback(QSpinBox* SpinBox, QWidget* Parent, IntValueChangedCallbackType Callback)
{
    QIntValueChanged* CallbackHandler = new QIntValueChanged(Callback, Parent);
    Parent->connect(SpinBox, SIGNAL(valueChanged(int)), CallbackHandler, SLOT(OnValueChanged(int)));
}

QSpinBox *AddSpinBox(QGroupBox *GroupBox, QWidget *Parent, const SSpinboxProperties &Properties)
{
    // add label with name
    AddLabel(GroupBox, Parent, Properties.s_Name);

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
    // add label with name
    AddLabel(GroupBox, Parent, Properties.s_Name);

    QSpinBox* SpinBox = CreateSpinBox(Parent, Properties);
    GroupBox->layout()->addWidget(SpinBox);
    AddCallback(SpinBox, Parent, Callback);
}

void AddSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SSpinboxProperties& Properties, const std::string& ParameterName, CCommandStackController& Controller)
{
    // add label with name
    AddLabel(GroupBox, Parent, Properties.s_Name);

    QSpinBox* SpinBox = CreateSpinBox(Parent, Properties);
    GroupBox->layout()->addWidget(SpinBox);
    ConnectSpinbox(SpinBox, Parent, ParameterName, Controller);
}


void AddSpinBox(QGridLayout *Layout, QWidget *Parent, int X, int Y, const SSpinboxProperties &Properties, IntValueChangedCallbackType Callback)
{
    QSpinBox* SpinBox = CreateSpinBox(Parent, Properties);
    Layout->addWidget(SpinBox, Y, X);
    AddCallback(SpinBox, Parent, Callback);
}

void AddSpinBox(QGridLayout* Layout, QWidget * Parent, int X, int Y, const SSpinboxProperties& Properties, const std::string& ParameterName, CCommandStackController& Controller)
{
    QSpinBox* SpinBox = CreateSpinBox(Parent, Properties);
    Layout->addWidget(SpinBox, Y, X);
    ConnectSpinbox(SpinBox, Parent, ParameterName, Controller);
}

QComboBox* CreateComboBox(QWidget* Parent, const SComboboxProperties& Properties)
{
    QComboBox* ComboBox = new QComboBox(Parent);
    for(auto& Item : Properties.s_Selections)
    {
        ComboBox->addItem(QString::fromStdString(Item));
    }
    ComboBox->setCurrentIndex(Properties.s_DefaultSelection);
    return ComboBox;
}

void AddCallback(QComboBox* ComboBox, QWidget* Parent, IntValueChangedCallbackType Callback)
{
    QIntValueChanged* CallbackHandler = new QIntValueChanged(Callback, Parent);
    Parent->connect(ComboBox, SIGNAL(currentIndexChanged(int)), CallbackHandler, SLOT(OnValueChanged(int)));
}

void AddComboBox(QGridLayout *Layout, QWidget *Parent, int X, int Y, const SComboboxProperties &Properties, IntValueChangedCallbackType Callback)
{
    QComboBox* ComboBox = CreateComboBox(Parent, Properties);
    Layout->addWidget(ComboBox, Y, X);
    AddCallback(ComboBox, Parent, Callback);
}

void AddComboBox(QGroupBox* GroupBox, QWidget* Parent, const SComboboxProperties& Properties, IntValueChangedCallbackType Callback)
{
    QComboBox* ComboBox = CreateComboBox(Parent, Properties);
    GroupBox->layout()->addWidget(ComboBox);
    AddCallback(ComboBox, Parent, Callback);
}

void AddComboBox(QGridLayout *Layout, QWidget *Parent, int X, int Y, const SComboboxProperties &Properties, const std::string& ParameterName, CCommandStackController& Controller)
{
    QComboBox* ComboBox = CreateComboBox(Parent, Properties);
    Layout->addWidget(ComboBox, Y, X);
    ConnectCombobox(ComboBox, Parent, ParameterName, Controller);
}

}
