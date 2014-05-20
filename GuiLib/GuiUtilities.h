#ifndef GUIUTILITIES_H
#define GUIUTILITIES_H

#include <string>
#include <vector>
#include <functional>

class QDoubleSpinBox;
class QSpinBox;
class QGroupBox;
class QWidget;
class QGridLayout;

namespace guiutils
{

typedef std::function<void(double)> DoubleValueChangedCallbackType;
typedef std::function<void(int)> IntValueChangedCallbackType;
typedef std::function<void()> SimpleCallbackType;
typedef std::function<void(bool)> BoolValueChangedCallbackType;

QGroupBox* AddGroupBox(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name);

void AddLabel(QGroupBox *GroupBox, QWidget *Parent, const std::string& Name);

void AddLabel(QGridLayout *Layout, QWidget *Parent, int X, int Y, const std::string& Name);

void AddSmallButton(QGridLayout* Layout, QWidget *Parent, int X, int Y, const std::string& Name, SimpleCallbackType Callback);

void AddSmallButton(QGridLayout* Layout, QWidget *Parent, int X, int Y, const std::string& Name, BoolValueChangedCallbackType Callback);


struct SDoubleSpinboxProperties
{
    std::string s_Name;
    double s_Default;
    double s_Min;
    double s_Max;
    double s_Step;
    int s_NumDecimals;
};

void AddDoubleSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SDoubleSpinboxProperties& Properties, DoubleValueChangedCallbackType Callback);

void AddDoubleSpinBox(QGridLayout* Layout, QWidget * Parent, int X, int Y, const SDoubleSpinboxProperties& Properties, DoubleValueChangedCallbackType Callback);


struct SSpinboxProperties
{
    std::string s_Name;
    int s_Default;
    int s_Min;
    int s_Max;
    int s_Step;
};

void AddSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SSpinboxProperties& Properties, IntValueChangedCallbackType Callback);

void AddSpinBox(QGridLayout* Layout, QWidget * Parent, int X, int Y, const SSpinboxProperties& Properties, IntValueChangedCallbackType Callback);


struct SComboboxProperties
{
    std::string s_Name;
    std::vector<std::string> s_Selections;
    int s_DefaultSelection;
};

void AddComboBox(QGridLayout* Layout, QWidget* Parent, int X, int Y, const SComboboxProperties& Properties, IntValueChangedCallbackType Callback);

}

#endif // GUIUTILITIES_H
