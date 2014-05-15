#include "QKeyboardWidget.h"
#include "ui_QKeyboardWidget.h"
#include "Notes.h"
#include "Controller.h"

QKeyboardWidget::QKeyboardWidget(CController& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QKeyboardWidget)
  , m_Controller(Controller)
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
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_D_clicked()
{
    m_Note = ENote::D;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_E_clicked()
{
    m_Note = ENote::E;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_F_clicked()
{
    m_Note = ENote::F;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_G_clicked()
{
    m_Note = ENote::G;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_A_clicked()
{
    m_Note = ENote::A;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_B_clicked()
{
    m_Note = ENote::B;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_Cplus1_clicked()
{
    m_Note = ENote::C;
    m_Controller.OnNoteOn(m_Note, static_cast<EOctave>(static_cast<int>(m_Octave)+1));
}

void QKeyboardWidget::on_toolButton_Csharp_clicked()
{
    m_Note = ENote::Csharp;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_Dsharp_clicked()
{
    m_Note = ENote::Dsharp;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_Asharp_clicked()
{
    m_Note = ENote::Asharp;
    UpdateNote();
}

void QKeyboardWidget::UpdateNote()
{
    m_Controller.OnNoteOn(m_Note, m_Octave);
}

void QKeyboardWidget::on_spinBox_Octave_valueChanged(int arg1)
{
    m_Octave = static_cast<EOctave>(arg1);
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_Gsharp_clicked()
{
    m_Note = ENote::Gsharp;
    UpdateNote();
}

void QKeyboardWidget::on_toolButton_Fsharp_clicked()
{
    m_Note = ENote::Fsharp;
    UpdateNote();
}
