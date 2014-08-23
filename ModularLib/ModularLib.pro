TARGET = ModularLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += ConstFilter.cpp \
    PhasorFilter.cpp \
    OperatorFilter.cpp \
    AmpFilter.cpp \
    AmpModule.cpp \
    PhasorModule.cpp \
    OperatorModule.cpp \
    ConstModule.cpp \
    ModuleManager.cpp \
    ModuleFactory.cpp

HEADERS += ConstFilter.h \ 
    PhasorFilter.h \
    OperatorFilter.h \
    AmpFilter.h \
    ModularModuleI.h \
    AmpModule.h \
    PhasorModule.h \
    OperatorModule.h \
    ConstModule.h \
    ModuleManager.h \
    ModuleFactoryI.h \
    ModuleFactory.h

INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Interfaces


unix {
    target.path = /usr/lib
    INSTALLS += target
}
#TODO dependencies!
CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/ModularLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/ModularLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
