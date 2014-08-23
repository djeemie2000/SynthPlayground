#ifndef MODULARFACTORYWIDGET_H
#define MODULARFACTORYWIDGET_H

#include <memory>
#include <QWidget>

class CModuleManager;

namespace Ui {
class QModularFactoryWidget;
}

class QModularFactoryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QModularFactoryWidget(std::shared_ptr<CModuleManager> Manager, QWidget *parent = 0);
    ~QModularFactoryWidget();

private slots:
    void on_pushButton_Create_clicked();

    void on_pushButton_Remove_clicked();

private:
    Ui::QModularFactoryWidget *ui;
    std::shared_ptr<CModuleManager> m_Manager;
};

#endif // MODULARFACTORYWIDGET_H
