
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth8
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

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    LIBS += -L./../build-dir/Debug/CommandStackLib
    LIBS += -L./../build-dir/Debug/GuiLib
    LIBS += -L./../build-dir/Debug/AlsaMidiLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    LIBS += -L./../build-dir/Release/CommandStackLib
    LIBS += -L./../build-dir/Release/GuiLib
    LIBS += -L./../build-dir/Release/AlsaMidiLib
}

LIBS += -lSynthLib
LIBS += -lCommandStackLib
LIBS += -lGuiLib
LIBS += -lAlsaMidiLib
LIBS += -lasound

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Synth8
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Synth8
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
