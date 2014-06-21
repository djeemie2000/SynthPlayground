#ifndef QPATCHMANAGERWIDGET_H
#define QPATCHMANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class QPatchManagerWidget;
}

class CCommandStackController;

class QPatchManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QPatchManagerWidget(CCommandStackController& Controller, QWidget *parent = 0);
    ~QPatchManagerWidget();

private slots:
    void on_pushButton_Load_clicked();

    void on_pushButton_Save_clicked();

    void on_pushButton_Default_clicked();

private:
    Ui::QPatchManagerWidget *ui;


    CCommandStackController& m_Controller;
};

#endif // QPATCHMANAGERWIDGET_H
