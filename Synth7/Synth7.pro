
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Synth7
TEMPLATE = app

CONFIG   += c++11 (Qt5)

SOURCES += main.cpp\
        mainwindow.cpp \
    Controller.cpp \
    QAudioIoDevice.cpp \
    QView.cpp \
    Pitch.cpp \
    StepSequencer.cpp \
    Notes.cpp \
    SelectableCombinorFactory.cpp \
    SelectableOperatorFactory.cpp

HEADERS  += mainwindow.h \
    Controller.h \
    WriteWavFile.h \
    ReadWavFile.h \
    QAudioIoDevice.h \
    GranularSamplePlayer.h \
    PhaseStep.h \
    View.h \
    QView.h \
    SampleGrabber.h \
    PseudoSin.h \
    FullPseudoSin.h \
    NoOp.h \
    RampUp.h \
    RampDown.h \
    Square.h \
    InvSquare.h \
    PhaseGenerator.h \
    FeedbackOperator.h \
    FlipOperator.h \
    MirrorOperator.h \
    HardKneeShaper.h \
    CenteredShaper.h \
    PhaseDecreaseCondition.h \
    Smoother.h \
    SelectableOperator.h \
    Triangle.h \
    SymmetricalOperator.h \
    8BitFX.h \
    TriangularLFO.h \
    CrossFader.h \
    DetunedSelectableOscillator.h \
    SquareWave.h \
    OscillatorStage.h \
    Combinor.h \
    SelectableCombinor.h \
    Conversions.h \
    Notes.h \
    Pitch.h \
    WaveFolder.h \
    StepSequencer.h \
    SelectableCombinorFactory.h \
    OnePoleFilter.h \
    SelectableOperatorFactory.h \
    NonLinearShaper.h \
    BasicEnvelope.h \
    PeriodicThreadRunner.h

FORMS    += mainwindow.ui
