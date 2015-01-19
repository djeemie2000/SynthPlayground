#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <memory>
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
    explicit QGenericModuleWidget(std::weak_ptr<IModularModule> Module,
                                  CCommandStackController& CommandStackController,
                                  QWidget *parent = 0);
    ~QGenericModuleWidget();

    QGroupBox* GetParametersGroupBox();

public slots:
    void OnUpdateConnections();

private slots:
    void on_checkBox_Outputs_clicked(bool checked);

private:
    Ui::QGenericModuleWidget *ui;

    std::weak_ptr<IModularModule> m_Module;
};

#endif // QGENERICMODULEWIDGET_H
