
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Scope
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Controllers
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../GuiLib
INCLUDEPATH += ./../JackLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    LIBS += -L./../build-dir/Debug/CommandStackLib
    LIBS += -L./../build-dir/Debug/GuiLib
    LIBS += -L./../build-dir/Debug/JackLib
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    LIBS += -L./../build-dir/Release/CommandStackLib
    LIBS += -L./../build-dir/Release/GuiLib
    LIBS += -L./../build-dir/Release/JackLib
}

LIBS += -lSynthLib
LIBS += -lCommandStackLib
LIBS += -lGuiLib
LIBS += -lJackLib
LIBS += -ljack

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Scope
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Scope
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
