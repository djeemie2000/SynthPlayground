TARGET = ModularLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += Filters/ControllerBankFilter.cpp \
    Filters/PhasorFilter.cpp \
    Filters/OperatorFilter.cpp \
    Filters/AmpFilter.cpp \
    Modules/AmpModule.cpp \
    Modules/PhasorModule.cpp \
    Modules/OperatorModule.cpp \
    Modules/ControllerBankModule.cpp \
    ModuleManager.cpp \
    ModuleFactory.cpp \
    Filters/MidiNoteFilter.cpp \
    TriggerMidiNoteHandler.cpp \
    Modules/MidiNoteModule.cpp \
    Filters/LpfFilter.cpp \
    Modules/LpfModule.cpp \
    Filters/LFOBankFilter.cpp \
    Modules/LFOBankModule.cpp \
    Filters/SimpleOscillatorFilter.cpp \
    Modules/SimpleOscillatorModule.cpp \
    Filters/StereoDelayFilter.cpp \
    Modules/StereoDelayModule.cpp \
    Filters/ADSREnvelopeBankFilter.cpp \
    Modules/ADSREnvelopeBankModule.cpp \
    Filters/SkewerFilter.cpp

HEADERS += Filters/ControllerBankFilter.h \
    Filters/PhasorFilter.h \
    Filters/OperatorFilter.h \
    Filters/AmpFilter.h \
    ModularModuleI.h \
    Modules/AmpModule.h \
    Modules/PhasorModule.h \
    Modules/OperatorModule.h \
    Modules/ControllerBankModule.h \
    ModuleManager.h \
    ModuleFactoryI.h \
    ModuleFactory.h \
    Filters/MidiNoteFilter.h \
    TriggerMidiNoteHandler.h \
    Modules/MidiNoteModule.h \
    ModuleParameterVisitorI.h \
    Filters/LpfFilter.h \
    Modules/LpfModule.h \
    Filters/LFOBankFilter.h \
    Modules/FOBankModule.h \
    Filters/SimpleOscillatorFilter.h \
    Modules/SimpleOscillatorModule.h \
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
