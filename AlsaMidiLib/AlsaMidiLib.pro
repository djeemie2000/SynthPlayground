TARGET = AlsaMidiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += \
    LogMidiInputHandler.cpp \
    MidiInput.cpp

HEADERS += \
    MidiInputHandlerI.h \
    LogMidiInputHandler.h \
    MidiInput.h

LIBS += -lasound

unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug:DESTDIR = ../build-dir/Debug/AlsaMidiLib
release:DESTDIR = ../build-dir/Release/AlsaMidiLib

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
