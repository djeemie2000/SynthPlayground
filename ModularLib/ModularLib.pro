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
    MidiHandlers/TriggerMidiNoteHandler.cpp \
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
    Modules/StepSequencerModule.cpp \
    MidiHandlers/MidiControllerValueHandler.cpp \
    Filters/MidiControllerBankFilter.cpp \
    Modules/MidiControllerBankModule.cpp \
    Filters/EnvelopeFollowerFilter.cpp \
    Modules/EnvelopeFollowerModule.cpp \
    Filters/DelayLineFilter.cpp \
    Modules/DelayLineModule.cpp \
    Filters/StereoMixerFilter.cpp \
    Modules/StereoMixerModule.cpp \
    Filters/MidiLoggerFilter.cpp \
    Modules/MidiLoggerModule.cpp \
    Filters/AsymmetricAmpFilter.cpp \
    Modules/AsymmetricAmpModule.cpp \
    CountModuleParameterVisitor.cpp \
    Modules/MultiStepSequencerModule.cpp \
    Filters/MultiStepSequencerFilter.cpp \
    Filters/ClockFilter.cpp \
    Modules/ClockModule.cpp \
    Filters/FMFilter.cpp \
    Modules/FMModule.cpp \
    Filters/RandomGateFilter.cpp \
    Modules/RandomGateModule.cpp \
    Filters/ExtendedModulatorFilter.cpp \
    Modules/ExtendedModulatorModule.cpp \
    Filters/LimiterFilter.cpp \
    Modules/LimiterModule.cpp \
    Filters/BipolarLimiterFilter.cpp \
    Filters/UnipolarLimiterFilter.cpp \
    Modules/BipolarLimiterModule.cpp \
    Modules/UnipolarLimiterModule.cpp \
    Filters/SlewLimiterFilter.cpp \
    Modules/SlewLimiterModule.cpp \
    Filters/OneVoltPerOctaveFilter.cpp \
    Modules/OneVoltPerOctaveModule.cpp \
    Filters/HpfFilter.cpp \
    Modules/HpfModule.cpp \
    Filters/GranularFilter.cpp \
    Modules/GranularModule.cpp \
    Modules/PhaseShifterModule.cpp \
    Filters/PhaseShifterFilter.cpp \
    Filters/WaveTableFilter.cpp \
    Modules/WaveTableModule.cpp \
    Filters/KarplusStrongFilter.cpp \
    Modules/KarplusStrongModule.cpp \
    Filters/DecayEnvelopeFilter.cpp \
    Modules/DecayEnvelopeModule.cpp \
    Filters/ToggleGateFilter.cpp \
    Modules/ToggleGateModule.cpp \
    Filters/ScalerFilter.cpp \
    Modules/ScalerModule.cpp \
    Filters/ControllerChangeFilter.cpp \
    Modules/ControllerChangeModule.cpp \
    Filters/RingSequencerFilter.cpp \
    Modules/RingSequencerModule.cpp \
    Filters/MidiOctaveGateFilter.cpp \
    Modules/MidiOctaveGateModule.cpp \
    Filters/SimpleLooperFilter.cpp \
    Filters/BasicSamplerFilter.cpp \
    Modules/BasicSamplerModule.cpp \
    FilterBuffers.h \
    Filters/BufferingFilter.cpp \
    Modules/ScopeModule.cpp \
    Filters/BinaryOscillatorFilter.cpp \
    Modules/BinaryOscillatorModule.cpp \
    Filters/WaveShaperA116Filter.cpp \
    Modules/WaveShaperA116Module.cpp \
    Filters/CombinedOperatorFilter.cpp \
    Modules/CombinedOperatorModule.cpp \
    Filters/IntSimpleOscillatorFilter.cpp \
    Modules/IntSimpleOscillatorModule.cpp \
    Filters/IntCombinedOperatorFilter.cpp \
    Modules/IntCombinedOperatorModule.cpp \
    Filters/IntKarplusStrongFilter.cpp \
    Modules/IntKarplusStrongModule.cpp \
    Filters/IntFeedbackDelayFilter.cpp \
    Modules/IntFeedbackDelayModule.cpp \
    Filters/ChebishevFilter.cpp \
    Modules/ChebishevModule.cpp

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
    MidiHandlers/TriggerMidiNoteHandler.h \
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
    Modules/StepSequencerModule.h \
    MidiHandlers/MidiControllerValueHandler.h \
    Filters/MidiControllerBankFilter.h \
    Modules/MidiControllerBankModule.h \
    Filters/EnvelopeFollowerFilter.h \
    Modules/EnvelopeFollowerModule.h \
    Filters/DelayLineFilter.h \
    Modules/DelayLineModule.h \
    Filters/StereoMixerFilter.h \
    Modules/StereoMixerModule.h \
    Filters/MidiLoggerFilter.h \
    Modules/MidiLoggerModule.h \
    Filters/AsymmetricAmpFilter.h \
    Modules/AsymmetricAmpModule.h \
    CountModuleParameterVisitor.h \
    Modules/MultiStepSequencerModule.h \
    Filters/MultiStepSequencerFilter.h \
    Filters/ClockFilter.h \
    Modules/ClockModule.h \
    Filters/FMFilter.h \
    Modules/FMModule.h \
    Filters/RandomGateFilter.h \
    Modules/RandomGateModule.h \
    Filters/ExtendedModulatorFilter.h \
    Modules/ExtendedModulatorModule.h \
    Filters/LimiterFilter.h \
    Modules/LimiterModule.h \
    Filters/BipolarLimiterFilter.h \
    Filters/UnipolarLimiterFilter.h \
    Modules/UnipolarLimiterModule.h \
    Modules/BipolarLimiterModule.h \
    Filters/SlewLimiterFilter.h \
    Modules/SlewLimiterModule.h \
    Filters/OneVoltPerOctaveFilter.h \
    Modules/OneVoltPerOctaveModule.h \
    Filters/HpfFilter.h \
    Modules/HpfModule.h \
    Filters/GranularFilter.h \
    Modules/GranularModule.h \
    Modules/PhaseShifterModule.h \
    Filters/PhaseShifterFilter.h \
    Filters/WaveTableFilter.h \
    Modules/WaveTableModule.h \
    Filters/KarplusStrongFilter.h \
    Modules/KarplusStrongModule.h \
    Filters/DecayEnvelopeFilter.h \
    Modules/DecayEnvelopeModule.h \
    Filters/ToggleGateFilter.h \
    Modules/ToggleGateModule.h \
    Filters/ScalerFilter.h \
    Modules/ScalerModule.h \
    Filters/ControllerChangeFilter.h \
    Modules/ControllerChangeModule.h \
    Filters/RingSequencerFilter.h \
    Modules/RingSequencerModule.h \
    Filters/MidiOctaveGateFilter.h \
    Modules/MidiOctaveGateModule.h \
    Filters/SimpleLooperFilter.h \
    Filters/BasicSamplerFilter.h \
    Modules/BasicSamplerModule.h \
    Filters/BufferingFilter.h \
    Modules/ScopeModule.h \
    Filters/BinaryOscillatorFilter.h \
    Modules/BinaryOscillatorModule.h \
    Filters/WaveShaperA116Filter.h \
    Modules/WaveShaperA116Module.h \
    Filters/CombinedOperatorFilter.h \
    Modules/CombinedOperatorModule.h \
    Filters/IntSimpleOscillatorFilter.h \
    Modules/IntSimpleOscillatorModule.h \
    Filters/IntCombinedOperatorFilter.h \
    Modules/IntCombinedOperatorModule.h \
    Filters/IntKarplusStrongFilter.h \
    Modules/IntKarplusStrongModule.h \
    Filters/IntFeedbackDelayFilter.h \
    Modules/IntFeedbackDelayModule.h \
    Filters/ChebishevFilter.h \
    Modules/ChebishevModule.h

INCLUDEPATH += ./Filters
INCLUDEPATH += ./Modules
INCLUDEPATH += ./MidiHandlers
INCLUDEPATH += ./../CommandStackLib
INCLUDEPATH += ./../JackLib
INCLUDEPATH += ./../SynthLib
INCLUDEPATH += ./../SynthLib/Interfaces
INCLUDEPATH += ./../SynthLib/Granular
INCLUDEPATH += ./../SynthLib/Looper
INCLUDEPATH += ./../IntSynthLib
INCLUDEPATH += ./../MidiLib
INCLUDEPATH += ./../Utilities

win32 {
    INCLUDEPATH += "C:/Program Files (x86)/Jack/includes"
}

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
