#ifndef QGENERICMODULEWIDGET_H
#define QGENERICMODULEWIDGET_H

#include <memory>
#include <map>
#include <QWidget>

class IModularModule;
class CJackConnectionManager;
class CCommandStackController;

namespace Ui {
class QGenericModuleWidget;
}

class QGroupBox;
class QLabel;

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

public slots:
    void OnConnectionChanged(QString OutputPortName, QString InputPortName, bool Connect);

private slots:
    void on_checkBox_Outputs_clicked(bool checked);

private:
    void AddParameters(CCommandStackController& CommandStackController);
    void AddOutputs();
    void AddConnectionListener();

    Ui::QGenericModuleWidget *ui;

    std::weak_ptr<IModularModule> m_Module;
    std::weak_ptr<CJackConnectionManager> m_ConnectionManager;

    std::map<std::string, QLabel*> m_OutputConnectionLabel;
};

#endif // QGENERICMODULEWIDGET_H
