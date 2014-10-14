#ifndef QLEDWIDGET_H
#define QLEDWIDGET_H

#include <QLabel>
#include <QPixmap>

class QStatusLedWidget : public QLabel
{

Q_OBJECT

public:
    explicit QStatusLedWidget(QWidget* parent = 0);

public slots:
    void OnStatus(bool Status);

private:
    QPixmap m_LedOnPixMap;
    QPixmap m_LedOffPixMap;
};

#endif // QLEDWIDGET_H
