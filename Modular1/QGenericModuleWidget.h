#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <QWidget>

class IModularModule;

namespace Ui {
class QGenericModuleWidget;
}

class QGenericModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGenericModuleWidget(IModularModule& Module, QWidget *parent = 0);
    ~QGenericModuleWidget();

private:
    Ui::QGenericModuleWidget *ui;

    void AddInput(QString Name);
    void AddOutput(QString Name);
};

#endif // QGENERICMODULEWIDGET_H
