TARGET = JackLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += \
        JackAudioOutput.cpp 

HEADERS += \
        JackAudioOutput.h 

INCLUDEPATH += ./../SynthLib

LIBS += -ljack

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
