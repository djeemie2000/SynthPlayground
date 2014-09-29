TARGET = AlsaLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += AlsaMidiInput.cpp 

HEADERS += AlsaMidiInput.h

INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../MidiLib

LIBS += -lasound

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/AlsaLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/AlsaLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR

