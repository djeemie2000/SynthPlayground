TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

INCLUDEPATH += ./../JackLib

CONFIG(debug, debug|release) {
    LIBS += -L./../build-dir/Debug/JackLib
    PRE_TARGETDEPS += ./../build-dir/Debug/JackLib/libJackLib.a
}
CONFIG(release, debug|release) {
    LIBS += -L./../build-dir/Release/JackLib
    PRE_TARGETDEPS += ./../build-dir/Release/JackLib/libJackLib.a
}

LIBS += -lJackLib
win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Jack/includes"
    LIBS += "C:/Program Files (x86)/Jack/lib/libjack.lib"
}
unix {
    LIBS += -ljack
}
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/JackConnectionTool
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/JackConnectionTool
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
