
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth7
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp \
    QAudioIoDevice.cpp \
    QView.cpp \
    GuiUtilities.cpp \
    QGuiCallbacks.cpp \
    GuiItems.cpp


HEADERS  += mainwindow.h \  
    QAudioIoDevice.h \
    QView.h \
    GuiUtilities.h \
    QGuiCallbacks.h \
    GuiItems.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./../SynthLib

debug:LIBS += -L./../build-dir/Debug/SynthLib
release:LIBS += -L./../build-dir/Release/SynthLib

LIBS += -lSynthLib

debug:DESTDIR = ../build-dir/Debug/Synth7
release:DESTDIR = ../build-dir/Release/Synth7

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

