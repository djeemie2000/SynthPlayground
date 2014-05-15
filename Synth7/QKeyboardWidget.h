#ifndef QKEYBOARDWIDGET_H
#define QKEYBOARDWIDGET_H

#include <QWidget>
#include "Notes.h"

namespace Ui {
class QKeyboardWidget;
}

class CController;

class QKeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QKeyboardWidget(CController&, QWidget *parent = 0);
    ~QKeyboardWidget();

private slots:
    void on_toolButton_C_clicked();
    void on_toolButton_Csharp_clicked();
    void on_toolButton_D_clicked();
    void on_toolButton_Dsharp_clicked();
    void on_toolButton_E_clicked();
    void on_toolButton_F_clicked();
    void on_toolButton_Fsharp_clicked();
    void on_toolButton_G_clicked();
    void on_toolButton_Gsharp_clicked();
    void on_toolButton_A_clicked();
    void on_toolButton_Asharp_clicked();
    void on_toolButton_B_clicked();
    void on_toolButton_Cplus1_clicked();    
    void on_spinBox_Octave_valueChanged(int arg1);
        
private:
    void UpdateNote();
    
    Ui::QKeyboardWidget *ui;

    CController& m_Controller;
    ENote m_Note;
    EOctave m_Octave;
};

#endif // QKEYBOARDWIDGET_H
