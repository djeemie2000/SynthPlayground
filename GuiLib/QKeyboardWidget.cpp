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
{
    ui->setupUi(this);
}

QKeyboardWidget::~QKeyboardWidget()
{
    delete ui;
}

void QKeyboardWidget::on_toolButton_C_clicked()
{
    m_Note = ENote::C;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_D_clicked()
{
    m_Note = ENote::D;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_E_clicked()
{
    m_Note = ENote::E;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_F_clicked()
{
    m_Note = ENote::F;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_G_clicked()
{
    m_Note = ENote::G;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_A_clicked()
{
    m_Note = ENote::A;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_B_clicked()
{
    m_Note = ENote::B;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_Cplus1_clicked()
{
    m_Note = ENote::C;
    m_NoteHandler.OnNoteOn(m_Note, static_cast<EOctave>(static_cast<int>(m_Octave)+1));
}

void QKeyboardWidget::on_toolButton_Csharp_clicked()
{
    m_Note = ENote::Csharp;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_Dsharp_clicked()
{
    m_Note = ENote::Dsharp;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_Asharp_clicked()
{
    m_Note = ENote::Asharp;
    UpdateNoteHandler();
}

void QKeyboardWidget::UpdateNoteHandler()
{
    m_NoteHandler.OnNoteOn(m_Note, m_Octave);
}

void QKeyboardWidget::on_spinBox_Octave_valueChanged(int arg1)
{
    m_Octave = static_cast<EOctave>(arg1);
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_Gsharp_clicked()
{
    m_Note = ENote::Gsharp;
    UpdateNoteHandler();
}

void QKeyboardWidget::on_toolButton_Fsharp_clicked()
{
    m_Note = ENote::Fsharp;
    UpdateNoteHandler();
}
