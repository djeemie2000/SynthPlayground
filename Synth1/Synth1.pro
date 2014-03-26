#-------------------------------------------------
#
# Project created by QtCreator 2014-03-09T08:19:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = GranularSampler
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
        mainwindow.cpp \
    Controller.cpp \
    QAudioIoDevice.cpp \
    QView.cpp

HEADERS  += mainwindow.h \
    Controller.h \
    WriteWavFile.h \
    ReadWavFile.h \
    QAudioIoDevice.h \
    GranularSamplePlayer.h \
    PhaseStep.h \
    View.h \
    QView.h \
    SampleGrabber.h

FORMS    += mainwindow.ui
