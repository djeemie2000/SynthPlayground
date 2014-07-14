#include "QKeyboardWidget.h"
#include "ui_QKeyboardWidget.h"
#include "Notes.h"
#include "NoteHandlerI.h"

QKeyboardWidget::QKeyboardWidget(INoteHandler &NoteHandler, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QKeyboardWidget)
  , m_NoteHandler(NoteHandler)
  , m_Note(ENote::A)
  , m_Octave(EOctave::Octave2)
  , m_NoteOn(false)
  , m_RelativeOctave(0)
{
    ui->setupUi(this);
}

QKeyboardWidget::~QKeyboardWidget()
{
    delete ui;
}

void QKeyboardWidget::on_toolButton_C_clicked(bool checked)
{
    OnNoteClicked(ENote::C, 0, checked);
}

void QKeyboardWidget::on_toolButton_D_clicked(bool checked)
{
    OnNoteClicked(ENote::D, 0, checked);
}

void QKeyboardWidget::on_toolButton_E_clicked(bool checked)
{
    OnNoteClicked(ENote::E, 0, checked);
}

void QKeyboardWidget::on_toolButton_F_clicked(bool checked)
{
    OnNoteClicked(ENote::F, 0, checked);
}

void QKeyboardWidget::on_toolButton_G_clicked(bool checked)
{
    OnNoteClicked(ENote::G, 0, checked);
}

void QKeyboardWidget::on_toolButton_A_clicked(bool checked)
{
    OnNoteClicked(ENote::A, 0, checked);
}

void QKeyboardWidget::on_toolButton_B_clicked(bool checked)
{
    OnNoteClicked(ENote::B, 0, checked);
}

void QKeyboardWidget::on_toolButton_Cplus1_clicked(bool checked)
{
    OnNoteClicked(ENote::C, 1, checked);
}

void QKeyboardWidget::on_toolButton_Csharp_clicked(bool checked)
{
    OnNoteClicked(ENote::Csharp, 0, checked);
}

void QKeyboardWidget::on_toolButton_Dsharp_clicked(bool checked)
{
    OnNoteClicked(ENote::Dsharp, 0, checked);
}

void QKeyboardWidget::on_toolButton_Fsharp_clicked(bool checked)
{
    OnNoteClicked(ENote::Fsharp, 0, checked);
}

void QKeyboardWidget::on_toolButton_Gsharp_clicked(bool checked)
{
    OnNoteClicked(ENote::Gsharp, 0, checked);
}

void QKeyboardWidget::on_toolButton_Asharp_clicked(bool checked)
{
    OnNoteClicked(ENote::Asharp, 0, checked);
}

void QKeyboardWidget::UpdateNoteHandler()
{
    EOctave Octave = static_cast<EOctave>(static_cast<int>(m_Octave)+m_RelativeOctave);
    if(m_NoteOn)
    {
        // TODO note off of previous !!!
        m_NoteHandler.OnNoteOn(m_Note, Octave);
    }
    else
    {
        m_NoteHandler.OnNoteOff(m_Note, Octave);
    }
}

void QKeyboardWidget::on_spinBox_Octave_valueChanged(int arg1)
{
    m_Octave = static_cast<EOctave>(arg1);
    UpdateNoteHandler();
}

void QKeyboardWidget::OnNoteClicked(ENote Note, int RelativeOctave, bool Checked)
{
    m_Note = Note;
    m_NoteOn = Checked;
    m_RelativeOctave = RelativeOctave;
    UpdateNoteHandler();
    if(Checked)
    {
        // uncheck all buttons except the current clicked
        ui->toolButton_C->setChecked(m_Note==ENote::C && RelativeOctave==0);
        ui->toolButton_Csharp->setChecked(m_Note==ENote::Csharp);
        ui->toolButton_D->setChecked(m_Note==ENote::D);
        ui->toolButton_Dsharp->setChecked(m_Note==ENote::Dsharp);
        ui->toolButton_E->setChecked(m_Note==ENote::E);
        ui->toolButton_F->setChecked(m_Note==ENote::F);
        ui->toolButton_Fsharp->setChecked(m_Note==ENote::Fsharp);
        ui->toolButton_G->setChecked(m_Note==ENote::G);
        ui->toolButton_Gsharp->setChecked(m_Note==ENote::Gsharp);
        ui->toolButton_A->setChecked(m_Note==ENote::A);
        ui->toolButton_Asharp->setChecked(m_Note==ENote::Asharp);
        ui->toolButton_B->setChecked(m_Note==ENote::B);
        ui->toolButton_Cplus1->setChecked(m_Note==ENote::C && RelativeOctave==1);
    }
}

