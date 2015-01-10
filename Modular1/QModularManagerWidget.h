#ifndef MODULARFACTORYWIDGET_H
#define MODULARFACTORYWIDGET_H

#include <memory>
#include <QWidget>
#include <QString>

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
    void on_pushButton_RemoveAll_clicked();
    void on_pushButton_Default_clicked();
    void on_pushButton_Save_clicked();
    void on_pushButton_Load_clicked();
    void on_listWidget_ModuleNames_itemSelectionChanged();
    void on_listWidget_ModuleCategories_currentTextChanged(const QString &currentText);

private:
    void UpdateNames();

    Ui::QModularManagerWidget *ui;
    std::weak_ptr<CModular1Controller> m_Controller;
    QString m_Path;
};

#endif // MODULARFACTORYWIDGET_H
