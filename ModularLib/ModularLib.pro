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
    Filters/SkewerFilter.cpp \
    Modules/CombinorModule.cpp \
    Modules/PhaseSkewerModule.cpp \
    Filters/MixerFilter.cpp \
    Modules/MixerModule.cpp \
    Filters/CombinorFilter.cpp \
    Filters/CrossMixerFilter.cpp \
    Modules/CrossMixerModule.cpp \
    Filters/ModulatorFilter.cpp \
    Modules/ModulatorModule.cpp \
    Filters/WaveFolderFilter.cpp \
    Modules/WaveFolderModule.cpp \
    Filters/PosNegShaperFilter.cpp \
    Modules/PosNegShaperModule.cpp \
    Filters/LinSegOperatorFilter.cpp \
    Modules/LinSegOperatorModule.cpp \
    Filters/DetunerFilter.cpp \
    Modules/DetunerModule.cpp \
    Filters/MultiStageWaveFolderFilter.cpp \
    Modules/MultiStageWaveFolderModule.cpp \
    Filters/PeriodicSyncFilter.cpp \
    Modules/PeriodicSyncModule.cpp \
    Filters/Distortion1Filter.cpp \
    Modules/Distortion1Module.cpp \
    Filters/NoiseFilter.cpp \
    Modules/NoiseModule.cpp \
    Filters/SampleAndHoldFilter.cpp \
    Modules/SampleAndHoldModule.cpp \
    Filters/GlitchFilter.cpp \
    Modules/GlitchModule.cpp \
    Filters/MidiStepSequencerFilter.cpp \
    Modules/MidiStepSequencerModule.cpp \
    Filters/PeriodicTriggerFilter.cpp \
    Modules/PeriodicTriggerModule.cpp \
    Filters/StepSequencerFilter.cpp \
    Modules/StepSequencerModule.cpp

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
    Modules/LFOBankModule.h \
    Filters/SimpleOscillatorFilter.h \
    Modules/SimpleOscillatorModule.h \
    Filters/StereoDelayFilter.h \
    Modules/StereoDelayModule.h \
    Filters/ADSREnvelopeBankFilter.h \
    Modules/ADSREnvelopeBankModule.h \
    Filters/SkewerFilter.h \
    Modules/CombinorModule.h \
    Modules/PhaseSkewerModule.h \
    Filters/MixerFilter.h \
    Modules/MixerModule.h \
    Filters/CombinorFilter.h \
    Filters/CrossMixerFilter.h \
    Modules/CrossMixerModule.h \
    Filters/ModulatorFilter.h \
    Modules/ModulatorModule.h \
    Filters/WaveFolderFilter.h \
    Modules/WaveFolderModule.h \
    Filters/PosNegShaperFilter.h \
    Modules/PosNegShaperModule.h \
    Filters/LinSegOperatorFilter.h \
    Modules/LinSegOperatorModule.h \
    Filters/DetunerFilter.h \
    Modules/DetunerModule.h \
    Filters/MultiStageWaveFolderFilter.h \
    Modules/MultiStageWaveFolderModule.h \
    Filters/PeriodicSyncFilter.h \
    Modules/PeriodicSyncModule.h \
    Filters/Distortion1Filter.h \
    Modules/Distortion1Module.h \
    Filters/NoiseFilter.h \
    Modules/NoiseModule.h \
    Filters/SampleAndHoldFilter.h \
    Modules/SampleAndHoldModule.h \
    Filters/GlitchFilter.h \
    Modules/GlitchModule.h \
    Filters/MidiStepSequencerFilter.h \
    Modules/MidiStepSequencerModule.h \
    Filters/PeriodicTriggerFilter.h \
    Modules/PeriodicTriggerModule.h \
    Filters/StepSequencerFilter.h \
    Modules/StepSequencerModule.h

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
