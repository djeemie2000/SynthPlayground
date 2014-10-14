#include "QStatusLedWidget.h"

QStatusLedWidget::QStatusLedWidget(QWidget *parent)
 : QLabel(parent)
 , m_LedOnPixMap(20, 20)
 , m_LedOffPixMap(20, 20)
{
    m_LedOnPixMap.fill(Qt::green);
    m_LedOffPixMap.fill(Qt::gray);

    this->setFrameShape(QFrame::WinPanel);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setPixmap(m_LedOffPixMap);
}

void QStatusLedWidget::OnStatus(bool Status)
{
    if(Status)
    {
        setPixmap(m_LedOnPixMap);
    }
    else
    {
        setPixmap(m_LedOffPixMap);
    }
}
