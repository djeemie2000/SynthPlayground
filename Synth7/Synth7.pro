
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
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../GuiLib
INCLUDEPATH += ./../AlsaMidiLib

debug:LIBS += -L./../build-dir/Debug/SynthLib
debug:LIBS += -L./../build-dir/Debug/CommandStackLib
debug:LIBS += -L./../build-dir/Debug/GuiLib
debug:LIBS += -L./../build-dir/Debug/AlsaMidiLib
release:LIBS += -L./../build-dir/Release/SynthLib
release:LIBS += -L./../build-dir/Release/CommandStackLib
release:LIBS += -L./../build-dir/Release/GuiLib
release:LIBS += -L./../build-dir/Release/AlsaMidiLib

LIBS += -lSynthLib
LIBS += -lCommandStackLib
LIBS += -lGuiLib
LIBS += -lAlsaMidiLib
LIBS += -lasound

debug:DESTDIR = ../build-dir/Debug/Synth7
release:DESTDIR = ../build-dir/Release/Synth7

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
