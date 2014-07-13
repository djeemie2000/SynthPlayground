#ifndef QKEYBOARDWIDGET_H
#define QKEYBOARDWIDGET_H

#include <QWidget>
#include "Notes.h"

namespace Ui {
class QKeyboardWidget;
}

class INoteHandler;

class QKeyboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QKeyboardWidget(INoteHandler& NoteHandler, QWidget *parent = 0);
    ~QKeyboardWidget();

private slots:
    void on_toolButton_C_clicked(bool checked);
    void on_toolButton_Csharp_clicked(bool checked);
    void on_toolButton_D_clicked(bool checked);
    void on_toolButton_Dsharp_clicked(bool checked);
    void on_toolButton_E_clicked(bool checked);
    void on_toolButton_F_clicked(bool checked);
    void on_toolButton_Fsharp_clicked(bool checked);
    void on_toolButton_G_clicked(bool checked);
    void on_toolButton_Gsharp_clicked(bool checked);
    void on_toolButton_A_clicked(bool checked);
    void on_toolButton_Asharp_clicked(bool checked);
    void on_toolButton_B_clicked(bool checked);
    void on_toolButton_Cplus1_clicked(bool checked);
    void on_spinBox_Octave_valueChanged(int arg1);        

private:
    void OnNoteClicked(ENote Note, int RelativeOctave, bool Checked);
    void UpdateNoteHandler();
    
    Ui::QKeyboardWidget *ui;

    INoteHandler& m_NoteHandler;
    ENote m_Note;
    EOctave m_Octave;
    bool m_NoteOn;
    int m_RelativeOctave;
};

#endif // QKEYBOARDWIDGET_H
