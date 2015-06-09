#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qRegisterMetaType< QVector<float> >("QVector/Float");
    qRegisterMetaType<QVector<QPointF> >("QVector<QPointF>");

    return a.exec();
}
