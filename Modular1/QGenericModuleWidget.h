#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <QWidget>

namespace Ui {
class QGenericModuleWidget;
}

class QGenericModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QGenericModuleWidget(QWidget *parent = 0);
    ~QGenericModuleWidget();

private:
    Ui::QGenericModuleWidget *ui;
};

#endif // QGENERICMODULEWIDGET_H
