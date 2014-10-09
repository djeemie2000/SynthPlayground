TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)

SOURCES += main.cpp

INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../ModularLib
INCLUDEPATH += ./../ModularLib/Modules

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/JackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/JackLib/libJackLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Debug/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Debug/ModularLib/libModularLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/JackLib
    PRE_TARGETDEPS += ./../build-dir/Release/JackLib/libJackLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Release/ModularLib
    PRE_TARGETDEPS += ./../build-dir/Release/ModularLib/libModularLib.a
}

LIBS += -lModularLib
LIBS += -lMidiLib
LIBS += -lJackLib

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Jack/includes"
    LIBS += "C:/Program Files (x86)/Jack/lib/libjack.lib"
}
unix {
    LIBS += -ljack
}
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/JackMidiLoggerTool
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/JackMidiLoggerTool
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
