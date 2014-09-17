TARGET = SynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += StepSequencer.cpp \
    Notes.cpp \
    Controllers/Synth7Controller.cpp \
    Controllers/Synth8Controller.cpp \
    Controllers/Synth9Controller.cpp \
    Pitch.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp \
    StepSequencer2.cpp \
    Controllers/ScopeController.cpp \
    periodicsamplegrabberproxy.cpp \
    Controllers/Synth10Controller.cpp \
    Controllers/KeyboardController.cpp \
    Controllers/EffectsAppController.cpp \
    Controllers/StepSequencerController.cpp \
    Controllers/Synth11Controller.cpp \
    RingSequencerMidiControllerStep.cpp \
    Controllers/RingSequencerController.cpp \
    Controllers/Synth12Controller.cpp \
    WavFileReader.cpp \
    ReadWavFile.cpp \
    MidiNoteConverter.cpp

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
    Controllers/Synth7Controller.h \
    Controllers/Synth8Controller.h \
    Controllers/Synth9Controller.h \
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
    Controllers/Synth10Controller.h \
    SkewedInterpolatingOperator.h \
    InterpolatingOperatorI.h \
    PhaseSkewer.h \
    Controllers/KeyboardController.h \
    DCOperator.h \
    RampUpDown.h \
    SquareQuadratic.h \
    IntegerPowerShaper.h \
    AudioFilterI.h \
    Controllers/EffectsAppController.h \
    Controllers/StepSequencerController.h \
    PowerLawDistortion.h \
    ASREnvelope.h \
    ADEnvelope.h \
    Controllers/Synth11Controller.h \
    Inverter.h \
    ADSREnvelope.h \
    RingSequencerMidiControllerStep.h \
    Controllers/RingSequencerController.h \
    BpmPeriod.h \
    PosNegShaper.h \
    WaveTable.h \
    Controllers/Synth12Controller.h \
    WavFileReader.h \
    MidiNoteConverter.h \
    SimpleOscillator.h \
    LinSegOperator.h \
    Detuner.h \
    WaveFolder2.h \
    PeriodicTrigger.h \
    Gate.h


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
