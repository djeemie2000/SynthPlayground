#ifndef MODULARFACTORYWIDGET_H
#define MODULARFACTORYWIDGET_H

#include <memory>
#include <QWidget>

class CModular1Controller;

namespace Ui {
class QModularManagerWidget;
}

class QModularManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QModularManagerWidget(std::weak_ptr<CModular1Controller> Controller,
                                   QWidget *parent = 0);
    ~QModularManagerWidget();

signals:

private slots:
    void on_pushButton_Create_clicked();
    void on_pushButton_Remove_clicked();
    void on_pushButton_Capture_clicked();
    void on_pushButton_Restore_clicked();
    void on_pushButton_RemoveAll_clicked();

private:
    void UpdateNames();

    Ui::QModularManagerWidget *ui;
    std::weak_ptr<CModular1Controller> m_Controller;
};

#endif // MODULARFACTORYWIDGET_H
