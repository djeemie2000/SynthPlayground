TARGET = ModularLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += ConstFilter.cpp \
    PhasorFilter.cpp \
    OscillatorFilter.cpp \
    AmpFilter.cpp \
    AmpModule.cpp \
    PhasorModule.cpp

HEADERS += ConstFilter.h \ 
    PhasorFilter.h \
    OscillatorFilter.h \
    AmpFilter.h \
    ModularModuleI.h \
    AmpModule.h \
    PhasorModule.h

INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Interfaces


unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/ModularLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/ModularLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
