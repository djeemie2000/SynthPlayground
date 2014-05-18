#ifndef QSCOPEWIDGET_H
#define QSCOPEWIDGET_H

#include <QWidget>

namespace Ui {
class QScopeWidget;
}

class ISampleGrabber;

class QScopeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QScopeWidget(ISampleGrabber& Grabber, QWidget *parent = 0);
    ~QScopeWidget();

public slots:
    void OnSample(QVector<std::int16_t> Sample);

private slots:
    void on_toolButton_Grab_clicked();
    void on_toolButton_ZoomIn_clicked();
    void on_toolButton_ZoomOut_clicked();
    void on_checkBox_GrabRepeated_clicked(bool checked);
    void OnTimer();

private:
    Ui::QScopeWidget *ui;

    ISampleGrabber& m_Grabber;
    bool m_AutoGrab;
};

#endif // QSCOPEWIDGET_H
