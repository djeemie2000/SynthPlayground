TARGET = SynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += StepSequencer.cpp \
    Notes.cpp \
    Pitch.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp \
    StepSequencer2.cpp \
    Controllers/ScopeController.cpp \
    periodicsamplegrabberproxy.cpp \
    RingSequencerMidiControllerStep.cpp \
    WavFileReader.cpp \
    ReadWavFile.cpp \
    MidiNoteConverter.cpp \
    Granular/GrainUtilities.cpp

HEADERS += StepSequencer.h \
    Notes.h \
    PeriodicThreadRunner.h \
    ContinuousThreadRunner.h \
    8BitFX.h \
    BasicEnvelope.h \
    CenteredShaper.h \
    ClockUtilities.h \
    Combinor.h \
    ConstGenerator.h \
    Conversions.h \
    CrossFader.h \
    DetunedSelectableOscillator.h \
    FeedbackOperator.h \
    FlipOperator.h \
    FullPseudoSin.h \
    GranularSamplePlayer.h \
    HardKneeShaper.h \
    InvSquare.h \
    MirrorOperator.h \
    NonLinearShaper.h \
    NoOp.h \
    OnePoleFilter.h \
    CombinedOperatorStage.h \
    CombinedFoldedOperatorStage.h \
    PhaseDecreaseCondition.h \
    PhaseGenerator.h \
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
    Smoother.h \
    Square.h \
    SquareWave.h \
    SymmetricalOperator.h \
    Triangle.h \
    ScopeI.h \
    WaveFolder.h \
    WriteWavFile.h \
    TriangularLFO.h \
    PeriodicConstGenerator.h \
    StepSequencer2.h \
    PeriodicTicker.h \
    SampleGrabberI.h \
    StepSequencerI.h \
    BitFxI.h \
    WaveFolderI.h \
    NoteHandlerI.h \
    LPFilterI.h \
    NonLinearShaperI.h \
    CombinedOperatorStageI.h \
    CombinedFoldedOperatorStageI.h \
    AudioSourceI.h \
    Amp.h \
    Modulator.h \
    LFO.h \
    LFOBankI.h \
    DelayLine.h \
    FeedbackDelay.h \
    AREnvelope.h \
    ConstNumSamplesGenerator.h \
    FeedbackDelayI.h \
    AREnvelopeI.h \
    MasterVolumeI.h \
    PeriodicSampleGrabber.h \
    Controllers/ScopeController.h \
    AudioSource2I.h \
    AudioRendererI.h \
    PeriodicSampleGrabberI.h \
    periodicsamplegrabberproxy.h \
    FMOperatorStage.h \
    FMOperatorStageI.h \
    SkewedInterpolatingOperator.h \
    InterpolatingOperatorI.h \
    PhaseSkewer.h \
    DCOperator.h \
    RampUpDown.h \
    SquareQuadratic.h \
    IntegerPowerShaper.h \
    AudioFilterI.h \
    PowerLawDistortion.h \
    ASREnvelope.h \
    ADEnvelope.h \
    Inverter.h \
    ADSREnvelope.h \
    RingSequencerMidiControllerStep.h \
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
    WaveTables/WaveTableData.h


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
