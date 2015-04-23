TARGET = SynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += Notes.cpp \
    Pitch.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp \
    StepSequencer2.cpp \
    Controllers/ScopeController.cpp \
    periodicsamplegrabberproxy.cpp \
    WavFileReader.cpp \
    ReadWavFile.cpp \
    MidiNoteConverter.cpp \
    Granular/GrainUtilities.cpp \
    MultiStepSequencer.cpp

HEADERS += Notes.h \
    PeriodicThreadRunner.h \
    ContinuousThreadRunner.h \
    ClockUtilities.h \
    Combinor.h \
    ConstGenerator.h \
    Conversions.h \
    CrossFader.h \
    FeedbackOperator.h \
    FlipOperator.h \
    FullPseudoSin.h \
    HardKneeShaper.h \
    InvSquare.h \
    MirrorOperator.h \
    NonLinearShaper.h \
    NoOp.h \
    OnePoleFilter.h \
    PhaseDecreaseCondition.h \
    PhaseStep.h \
    Pitch.h \
    PseudoSin.h \
    RampDown.h \
    RampUp.h \
    ReadWavFile.h \
    SampleGrabber.h \
    SelectableCombinor.h \
    SelectableCombinorFactory.h \
    SelectableOperator.h \
    SelectableOperatorFactory.h \
    Square.h \
    SquareWave.h \
    SymmetricalOperator.h \
    Triangle.h \
    ScopeI.h \
    WaveFolder.h \
    WriteWavFile.h \
    PeriodicConstGenerator.h \
    StepSequencer2.h \
    PeriodicTicker.h \
    Amp.h \
    Modulator.h \
    LFO.h \
    DelayLine.h \
    FeedbackDelay.h \
    AREnvelope.h \
    ConstNumSamplesGenerator.h \
    PeriodicSampleGrabber.h \
    Controllers/ScopeController.h \
    PeriodicSampleGrabberI.h \
    periodicsamplegrabberproxy.h \
    FMOperatorStage.h \
    PhaseSkewer.h \
    DCOperator.h \
    RampUpDown.h \
    SquareQuadratic.h \
    IntegerPowerShaper.h \
    PowerLawDistortion.h \
    ASREnvelope.h \
    ADEnvelope.h \
    Inverter.h \
    ADSREnvelope.h \
    BpmPeriod.h \
    PosNegShaper.h \
    WaveTable.h \
    WavFileReader.h \
    MidiNoteConverter.h \
    SimpleOscillator.h \
    LinSegOperator.h \
    Detuner.h \
    WaveFolder2.h \
    PeriodicTrigger.h \
    Gate.h \
    Noise.h \
    SampleAndHold.h \
    GlitchOperator.h \
    EnvelopeFollower.h \
    DelayLine2.h \
    AsymmetricAmp.h \
    MultiStepSequencer.h \
    Trigger.h \
    DecayEnvelope.h \
    ClockPulse.h \
    FMFrequencyModulator.h \
    RandomGate.h \
    Limiter.h \
    SlewLimiter.h \
    OneVoltPerOctave.h \
    Granular/Grain.h \
    Granular/GrainBank.h \
    Granular/GrainTrigger.h \
    Granular/BufferGrabber.h \
    Granular/GrainWindow.h \
    Granular/GrainUtilities.h \
    PhaseShifter.h \
    wavetable2.h \
    WaveTables/WaveTableData.h \
    karplusstrong.h \
    ToggleGate.h \
    RingSequencer.h
    PhaseAccumulator.h


INCLUDEPATH += ./../MidiLib

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../build-dir/Debug/SynthLib
}
CONFIG(release, debug|release) {
    DESTDIR = ../build-dir/Release/SynthLib
}

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
