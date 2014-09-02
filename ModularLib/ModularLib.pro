TARGET = ModularLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += ControllerBankFilter.cpp \
    PhasorFilter.cpp \
    OperatorFilter.cpp \
    AmpFilter.cpp \
    AmpModule.cpp \
    PhasorModule.cpp \
    OperatorModule.cpp \
    ControllerBankModule.cpp \
    ModuleManager.cpp \
    ModuleFactory.cpp \
    MidiNoteFilter.cpp \
    TriggerMidiNoteHandler.cpp \
    MidiNoteModule.cpp \
    LpfFilter.cpp \
    LpfModule.cpp \
    LFOBankFilter.cpp \
    LFOBankModule.cpp \
    SimpleOscillatorFilter.cpp \
    SimpleOscillatorModule.cpp \
    Filters/StereoDelayFilter.cpp \
    Modules/StereoDelayModule.cpp \
    Filters/ADSREnvelopeBankFilter.cpp \
    Modules/ADSREnvelopeBankModule.cpp \
    Filters/SkewerFilter.cpp

HEADERS += ControllerBankFilter.h \ 
    PhasorFilter.h \
    OperatorFilter.h \
    AmpFilter.h \
    ModularModuleI.h \
    AmpModule.h \
    PhasorModule.h \
    OperatorModule.h \
    ControllerBankModule.h \
    ModuleManager.h \
    ModuleFactoryI.h \
    ModuleFactory.h \
    MidiNoteFilter.h \
    TriggerMidiNoteHandler.h \
    MidiNoteModule.h \
    ModuleParameterVisitorI.h \
    LpfFilter.h \
    LpfModule.h \
    LFOBankFilter.h \
    LFOBankModule.h \
    SimpleOscillatorFilter.h \
    SimpleOscillatorModule.h \
    Filters/StereoDelayFilter.h \
    Modules/StereoDelayModule.h \
    Filters/ADSREnvelopeBankFilter.h \
    Modules/ADSREnvelopeBankModule.h \
    Filters/SkewerFilter.h

INCLUDEPATH += ./Filters
INCLUDEPATH += ./Modules
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Interfaces
INCLUDEPATH += ./../MidiLib


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
