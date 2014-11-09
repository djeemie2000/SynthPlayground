TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)

SOURCES += main.cpp

INCLUDEPATH += ./../AlsaLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../SerialLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Debug/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Debug/SerialLib
    PRE_TARGETDEPS += ./../build-dir/Debug/SerialLib/libSerialLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Release/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
    LIBS += -L./../build-dir/Release/SerialLib
    PRE_TARGETDEPS += ./../build-dir/Release/SerialLib/libSerialLib.a
}

LIBS += -lMidiLib
LIBS += -lAlsaLib
LIBS += -lSerialLib

win32 {
}
unix {
    LIBS += -lasound
}
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Serial2AlsaMidiTool
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Serial2AlsaMidiTool
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
