TARGET = JackLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
        JackIOManager.cpp \
    JackMidiSource.cpp \
    JackConnectionManager.cpp \
    JackMidiRenderer.cpp \
    JackMidiHandler.cpp

HEADERS += \
        JackIOManager.h \
    JackMidiSource.h \
    JackConnectionManager.h \
    JackMidiRenderer.h \
    JackMidiHandler.h \
    JackWin32Port.h \
    IConnectionChangedListener.h

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../MidiLib

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Jack/includes"
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}


CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/JackLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/JackLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
