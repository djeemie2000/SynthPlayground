#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <memory>
#include <QWidget>

class IModularModule;
class CJackConnectionManager;
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
                                  std::weak_ptr<CJackConnectionManager> ConnectionManager,
                                  CCommandStackController& CommandStackController,
                                  QWidget *parent = 0);
    ~QGenericModuleWidget();

    QGroupBox* GetParametersGroupBox();

private slots:
    void on_checkBox_Outputs_clicked(bool checked);

private:
    void AddParameters(CCommandStackController& CommandStackController);
    void AddOutputs();

    Ui::QGenericModuleWidget *ui;

    std::weak_ptr<IModularModule> m_Module;
    std::weak_ptr<CJackConnectionManager> m_ConnectionManager;
};

#endif // QGENERICMODULEWIDGET_H
