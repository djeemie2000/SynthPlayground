#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <QWidget>

class IModularModule;
class CCommandStackController;

namespace Ui {
class QGenericModuleWidget;
}

class QGroupBox;

class QGenericModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGenericModuleWidget(IModularModule& Module, CCommandStackController& CommandStackController, QWidget *parent = 0);
    ~QGenericModuleWidget();

    QGroupBox* GetParametersGroupBox();

private:
    Ui::QGenericModuleWidget *ui;

    void AddInput(QString Name);
    void AddOutput(QString Name);
};

#endif // QGENERICMODULEWIDGET_H
