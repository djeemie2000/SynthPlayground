
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Modular
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
    mainwindow.cpp \
    ModuleGuiFactory.cpp \
    QGenericModuleWidget.cpp \
    QModularManagerWidget.cpp \
    GuiModuleDecorator.cpp

HEADERS  += mainwindow.h \
    ModuleGuiFactory.h \
    QGenericModuleWidget.h \
    QModularManagerWidget.h \
    GuiModuleDecorator.h

FORMS    += mainwindow.ui \
    QGenericModuleWidget.ui \
    QModularManagerWidget.ui

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Controllers
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../ModularLib
INCLUDEPATH += ./../GuiLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../JackLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SynthLib
    PRE_TARGETDEPS += ./../build-dir/Debug/SynthLib/libSynthLib.a
    LIBS += -L./../build-dir/Debug/CommandStackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/CommandStackLib/libCommandStackLib.a
    LIBS += -L./../build-dir/Debug/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Debug/ModularLib/libModularLib.a
    LIBS += -L./../build-dir/Debug/GuiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/GuiLib/libGuiLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Debug/JackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/JackLib/libJackLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SynthLib
    PRE_TARGETDEPS += ./../build-dir/Release/SynthLib/libSynthLib.a
    LIBS += -L./../build-dir/Release/CommandStackLib
    PRE_TARGETDEPS += ./../build-dir/Release/CommandStackLib/libCommandStackLib.a
    LIBS += -L./../build-dir/Release/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Release/ModularLib/libModularLib.a
    LIBS += -L./../build-dir/Release/GuiLib
    PRE_TARGETDEPS += ./../build-dir/Release/GuiLib/libGuiLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Release/JackLib
    PRE_TARGETDEPS += ./../build-dir/Release/JackLib/libJackLib.a
}

LIBS += -lSynthLib
LIBS += -lCommandStackLib
LIBS += -lModularLib
LIBS += -lGuiLib
LIBS += -lMidiLib
LIBS += -lJackLib
LIBS += -lasound
LIBS += -ljack

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Modular1
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Modular1
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR