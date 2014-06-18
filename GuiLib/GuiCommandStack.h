#ifndef GUICOMMANDSTACK_H
#define GUICOMMANDSTACK_H

#include <string>

class QWidget;
class QToolButton;
class QPushButton;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class CCommandStackController;

void ConnectCheckableToolButton(QToolButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller);
void ConnectSpinbox(QSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller);
void ConnectDoubleSpinbox(QDoubleSpinBox* SpinBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller);
void ConnectCombobox(QComboBox* ComboBox, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller);
void ConnectPushButton(QPushButton* Button, QWidget* Parent, const std::string& ParameterName, CCommandStackController& Controller);

#endif // GUICOMMANDSTACK_H
