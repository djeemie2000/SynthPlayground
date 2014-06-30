TARGET = JackSound
TEMPLATE = app
CONFIG += c++11 (Qt5)

SOURCES += main.cpp \ 
    JackAudioOutput.cpp

HEADERS += \
    JackAudioOutput.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += ../../SynthLib

LIBS += -ljack

debug {
    DESTDIR = ../build-dir/Debug/JackSound
}
release {
    DESTDIR = ../build-dir/Release/JackSound
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
