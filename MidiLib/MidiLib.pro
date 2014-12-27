TARGET = MidiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += \
    LogMidiInputHandler.cpp \
    NoteQueueMidiInputHandler.cpp \
    NoteCountMidiHandler.cpp \
    CommandStackMidiInputHandler.cpp \
    MidiInputController.cpp \
    MidiNotePitch.cpp \
    MultiMidiHandler.cpp \
    RawMidiParser.cpp

HEADERS += \
    MidiHandlerI.h \
    LogMidiInputHandler.h \
    NoteQueueMidiInputHandler.h \
    NoteCountMidiHandler.h \
    CommandStackMidiInputHandler.h \
    MidiInputController.h \
    MidiControllerHandlerI.h \
    MidiSourceI.h \
    MidiRendererI.h \
    MidiNotePitch.h \
    MultiMidiHandler.h \
    RawMidiParser.h

INCLUDEPATH += ./../CommandStackLib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/MidiLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/MidiLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
