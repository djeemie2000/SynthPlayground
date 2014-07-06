TARGET = MidiLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += \
    LogMidiInputHandler.cpp \
    AlsaMidiInput.cpp \
    MidiNoteConverter.cpp \
    NoteQueueMidiInputHandler.cpp \
    notecountmidiinputhandler.cpp \
    CommandStackMidiInputHandler.cpp \
    MidiInputController.cpp

HEADERS += \
    MidiInputHandlerI.h \
    LogMidiInputHandler.h \
    AlsaMidiInput.h \
    MidiNoteConverter.h \
    NoteQueueMidiInputHandler.h \
    notecountmidiinputhandler.h \
    CommandStackMidiInputHandler.h \
    MidiInputController.h \
    MidiControllerHandlerI.h

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../CommandStackLib

LIBS += -lasound

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
