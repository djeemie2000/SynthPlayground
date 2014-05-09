
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth7
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp \
    QAudioIoDevice.cpp \
    QView.cpp


HEADERS  += mainwindow.h \  
    QAudioIoDevice.h \
    QView.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./../SynthLib

LIBS += -L./../SynthLib -lSynthLib

debug:OBJECTS_DIR = ../build-dir/Synth7/Debug/
debug:UI_DIR = ../build-dir/Synth7/Debug/
debug:MOC_DIR = ../build-dir/Synth7/Debug/
release:OBJECTS_DIR = ../build-dir/Synth7/Release/
release:UI_DIR = ../build-dir/Synth7/Release/
release:MOC_DIR = ../build-dir/Synth7/Release/
