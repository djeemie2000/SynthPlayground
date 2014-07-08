
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth9
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../GuiLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../JackLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    LIBS += -L./../build-dir/Debug/CommandStackLib
    LIBS += -L./../build-dir/Debug/GuiLib
    LIBS += -L./../build-dir/Debug/MidiLib
    LIBS += -L./../build-dir/Debug/JackLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    LIBS += -L./../build-dir/Release/CommandStackLib
    LIBS += -L./../build-dir/Release/GuiLib
    LIBS += -L./../build-dir/Release/MidiLib
    LIBS += -L./../build-dir/Release/JackLib
}

LIBS += -lSynthLib
LIBS += -lCommandStackLib
LIBS += -lGuiLib
LIBS += -lMidiLib
LIBS += -lJackLib
LIBS += -lasound
LIBS += -ljack

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Synth9
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Synth9
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
