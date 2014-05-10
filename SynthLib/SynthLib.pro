TARGET = SynthLib
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11 (Qt5)

SOURCES += StepSequencer.cpp \
    Notes.cpp \
    Controller.cpp \
    Pitch.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp

HEADERS += StepSequencer.h \
    Notes.h \
    PeriodicThreadRunner.h \
    8BitFX.h \
    BasicEnvelope.h \
    CenteredShaper.h \
    ClockUtilities.h \
    Combinor.h \
    ConstGenerator.h \
    Controller.h \
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
    OscillatorStage.h \
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
    View.h \
    WaveFolder.h \
    WriteWavFile.h \
    TriangularLFO.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

debug:DESTDIR = ../build-dir/Debug/SynthLib
release:DESTDIR = ../build-dir/Release/SynthLib

OBJECTS_DIR = $$DESTDIR
UI_DIR = $$DESTDIR
MOC_DIR = $$DESTDIR
