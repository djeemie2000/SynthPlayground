#ifndef GUIUTILITIES_H
#define GUIUTILITIES_H

#include <string>

class QDoubleSpinBox;
class QSpinBox;
class QGroupBox;
class QWidget;

namespace guiutilities
{

struct SDoubleSpinboxProperties
{
    std::string s_Name;
    double s_Default;
    double s_Min;
    double s_Max;
    double s_Step;
    int s_NumDecimals;
};

QDoubleSpinBox* AddDoubleSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SDoubleSpinboxProperties& Properties);

struct SSpinboxProperties
{
    std::string s_Name;
    int s_Default;
    int s_Min;
    int s_Max;
    int s_Step;
};

QSpinBox* AddSpinBox(QGroupBox* GroupBox, QWidget * Parent, const SSpinboxProperties& Properties);

}

#endif // GUIUTILITIES_H
