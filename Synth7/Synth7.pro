
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth7
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../GuiLib

debug:LIBS += -L./../build-dir/Debug/SynthLib
debug:LIBS += -L./../build-dir/Debug/GuiLib
release:LIBS += -L./../build-dir/Release/SynthLib
release:LIBS += -L./../build-dir/Release/GuiLib

LIBS += -lSynthLib
LIBS += -lGuiLib

debug:DESTDIR = ../build-dir/Debug/Synth7
release:DESTDIR = ../build-dir/Release/Synth7

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

