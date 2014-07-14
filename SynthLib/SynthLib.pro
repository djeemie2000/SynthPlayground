TARGET = SynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += StepSequencer.cpp \
    Notes.cpp \
    Synth7Controller.cpp \
    Synth8Controller.cpp \
    Synth9Controller.cpp \
    Pitch.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp \
    StepSequencer2.cpp \
    ScopeController.cpp \
    periodicsamplegrabberproxy.cpp \
    Synth10Controller.cpp

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
    Synth7Controller.h \
    Synth8Controller.h \
    Synth9Controller.h \
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
    ScopeController.h \
    AudioSource2I.h \
    AudioRendererI.h \
    PeriodicSampleGrabberI.h \
    periodicsamplegrabberproxy.h \
    FMOperatorStage.h \
    FMOperatorStageI.h \
    Synth10Controller.h \
    SkewedInterpolatingOperator.h

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
