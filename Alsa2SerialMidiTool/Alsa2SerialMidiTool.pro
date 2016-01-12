TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

INCLUDEPATH += ./../AlsaLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../SerialLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/SerialLib
    PRE_TARGETDEPS += ./../build-dir/Debug/SerialLib/libSerialLib.a
    LIBS += -L./../build-dir/Debug/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Debug/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/SerialLib
    PRE_TARGETDEPS += ./../build-dir/Release/SerialLib/libSerialLib.a
    LIBS += -L./../build-dir/Release/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Release/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
}

LIBS += -lMidiLib
LIBS += -lAlsaLib
LIBS += -lSerialLib

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Alsa/includes"
    LIBS += "C:/Program Files (x86)/Alsa/lib/libAlsa.lib"
}
unix {
    LIBS += -lasound
}
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/Alsa2SerialMidiTool
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/Alsa2SerialMidiTool
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
