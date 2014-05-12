#ifndef GUIUTILITIES_H
#define GUIUTILITIES_H

#include <string>
#include <functional>

class QDoubleSpinBox;
class QSpinBox;
class QGroupBox;
class QWidget;

namespace guiutils
{

typedef std::function<void(double)> DoubleValueChangedCallbackType;
typedef std::function<void(int)> IntValueChangedCallbackType;

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

struct SSpinboxProperties
{
    std::string s_Name;
    int s_Default;
    int s_Min;
    int s_Max;
    int s_Step;
};

void AddSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SSpinboxProperties& Properties, IntValueChangedCallbackType Callback);

}

#endif // GUIUTILITIES_H
