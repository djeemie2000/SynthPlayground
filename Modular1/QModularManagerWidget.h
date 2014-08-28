#ifndef MODULARFACTORYWIDGET_H
#define MODULARFACTORYWIDGET_H

#include <memory>
#include <QWidget>

class CModuleManager;
class CModuleGuiFactory;

namespace Ui {
class QModularManagerWidget;
}

class QModularManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QModularManagerWidget(std::shared_ptr<CModuleManager> Manager,
                                   std::shared_ptr<CModuleGuiFactory> Factory,
                                   QWidget *parent = 0);
    ~QModularManagerWidget();

signals:

private slots:
    void on_pushButton_Create_clicked();

    void on_pushButton_Remove_clicked();

private:
    Ui::QModularManagerWidget *ui;
    std::shared_ptr<CModuleManager> m_Manager;
    std::shared_ptr<CModuleGuiFactory> m_Factory;
};

#endif // MODULARFACTORYWIDGET_H
