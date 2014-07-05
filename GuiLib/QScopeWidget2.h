#ifndef QSCOPEWIDGET2_H
#define QSCOPEWIDGET2_H

#include <QWidget>
#include "ScopeI.h"

namespace Ui {
class QScopeWidget2;
}

class IPeriodicSampleGrabber;

class QScopeWidget2 : public QWidget, public IScope<float>
{
    Q_OBJECT

public:
    explicit QScopeWidget2(IPeriodicSampleGrabber& Grabber, QWidget *parent = 0);
    ~QScopeWidget2();

    void SetSample(const SampleContainerType& Sample);

public slots:
    void OnSample(QVector<float> Sample);

private slots:
    void on_spinBox_GrabPeriod_valueChanged(int arg1);
    void on_spinBox_GrabSize_valueChanged(int arg1);
    void on_toolButton_ZoomHorizontalIn_clicked();
    void on_toolButton_ZoomHorizontalOut_clicked();
    void on_toolButton_ZoomVerticalIn_clicked();
    void on_toolButton_ZoomVerticalOut_clicked();

private:
    Ui::QScopeWidget2 *ui;

    IPeriodicSampleGrabber& m_Grabber;
};

#endif // QSCOPEWIDGET2_H
