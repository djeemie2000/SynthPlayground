TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

INCLUDEPATH += ./../AlsaLib
INCLUDEPATH += ./../MidiLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Debug/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Debug/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Debug/MidiLib/libMidiLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/AlsaLib
    PRE_TARGETDEPS += ./../build-dir/Release/AlsaLib/libAlsaLib.a
    LIBS += -L./../build-dir/Release/MidiLib
    PRE_TARGETDEPS += ./../build-dir/Release/MidiLib/libMidiLib.a
}

LIBS += -lMidiLib
LIBS += -lAlsaLib

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Alsa/includes"
    LIBS += "C:/Program Files (x86)/Alsa/lib/libAlsa.lib"
}
unix {
    LIBS += -lasound
}
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/AlsaMidiLoggerTool
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/AlsaMidiLoggerTool
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
